/** @file Store.cpp
*   @brief This file contains implementation of Store class
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*/

#include "Store.h"
#include "Product.h"
#include "Inventory.h"
#include "ShoppingCart.h"
#include <iostream>

using namespace SuperStore;

uint16_t Store::order_id = 0;

Store::Store(const std::string &name
            , InStreamHolder &stream)
    :InStreamWrapper(stream)
    ,m_name(name)
{
  m_pInventory = std::make_unique<Inventory>("local");
  m_cart = std::make_unique<ShoppingCart>(stream);
  this->order_id = 0;
}

Store::~Store()
{
}

std::string Store::getName() const
{
  return m_name;
}

uint16_t Store::getInventorySize() const
{
  return m_pInventory->getProductCount();
}

bool Store::addProductToInventory(std::unique_ptr<Product> product)
{
  // if there is already a product in the inventory with the same Id,
  // return false. product cannot be added to the inventory
  if(m_pInventory->hasProductById(product->getID()))
  {
    std::cout<<"ERROR!! Please choose a unique ID for every product\n";
    return false;
  }
  // add the product to the inventory
  return m_pInventory->addProduct(std::move(product));
}

bool Store::removeProductFromInventory(uint16_t id)
{
  // if no product is found with this id in the inventory then there is nothing
  // to delete. return false
  if(false == m_pInventory->hasProductById(id))
  {
    std::cout<<"No product found with id : "  << id << "\n";
    return false;
  }
  m_pInventory->removeProduct(id);
  return true;
}

void Store::displayInventory() const
{
  m_pInventory->displayCatalog();
}

void Store::displayMainMenu() const
{
  std::cout<<"********************************************************************************\n";
  std::cout<<"****************** WELCOME TO " << m_name << " SUPERMARKET ********************************\n";
  std::cout<<"********************************************************************************\n";
  std::cout<<"Please choose an option that represents you:\n";
  std::cout<<"1)Buy Products\n2)Manage Store\nEnter '0' to exit.\n";
  std::cout<<"Enter your choice:";
}


void Store::displayStoreAdminMenu() const
{
  std::cout<<"****************** STORE ADMIN MENU *******************************\n";
  std::cout<<"What would you like to do?]\n";
  std::cout<<"1)Add new product\n2)Remove existing product\n3)View Inventory\n" <<
  "0)Return to Main Menu\n";
  std::cout<<"Please enter your choice:";
}

void Store::displayCustomerMenu() const
{
  //m_pInventory->displayCatalog();
  std::cout<<"Please choose from the below options :\n" <<
  "0) Return too Main Menu\n1)Purchase a product\n2)Edit Shopping cart\n" <<
  "3) Checkout and Pay\nPlease Enter your choice : ";
}

std::unique_ptr<PurchaseOrder> Store::getPurchaseOrderFromStream()
{
  do
  {
    std::cout << "enter product id:";
    // try to read product id from the user
    auto product_id = getUint16FromStream(getInputStream());
    // if the user enters 0 or product doesnt exist in inventory
    // they need to retry
    if(!product_id || !m_pInventory->hasProductById(product_id))
    {
      break;
    }
    uint16_t quantity = 0;
    do
    {
      std::cout << "enter quantity : ";
      quantity = getUint16FromStream(getInputStream());
    }while(!quantity); // only accept a non zero quantity
    // Ensure the product is still present in the Inventory
    auto sp = m_pInventory->getProductById(product_id);
    if(sp)
    {
      return std::make_unique<PurchaseOrder>(++(this->order_id),
                                             sp,
					     quantity);
    }

  }while(true);
  return std::unique_ptr<PurchaseOrder> {};
}
void Store::purchaseProduct()
{
  m_pInventory->displayCatalog();
  do
  {
    // get all required inputs from the user and create
    // an order
    auto order = this->getPurchaseOrderFromStream();
    if(!order)
    {
      // if not successful, user needs to retry
      break;
    }
    // if order is successfully created, place it in the cart
    m_cart->addToCart(std::move(order));
  }while(true);
}

void Store::deleteOrder()
{
  uint16_t order_id;
  std::cout << "Please Enter the order id to be deleted : ";
  order_id = getUint16FromStream(getInputStream());
  m_cart->removeFromCart(order_id);
}

void Store::updateOrder()
{
  m_cart->updateOrder();
}
void Store::viewOrEditShoppingCart()
{
  uint16_t choice;
  do
  {
    m_cart->display();
    std::cout << "Please select a choice from below :\n";
    std::cout << "0) Done\n1)Delete an Order\n2)Update an order\n";
    std::cout << "Please enter your choice : ";
    choice = getUint16FromStream(getInputStream());
    switch(EditCartChoice(choice))
    {
      case EditCartChoice::DONE :
      {
        return;
      }
      case EditCartChoice::DELETE_ORDER:
      {
        this->deleteOrder();
        break;
      }
      case EditCartChoice::UPDATE_ORDER:
      {
        this->updateOrder();
        break;
      }
      default:
        break;
    }
  }while(choice);
}

void Store::serviceCustomer()
{
  int choice;
  do
  {
    this->displayCustomerMenu();
    choice = getIntFromStream(getInputStream());
    switch(CustomerMenuChoice(choice))
    {
      case CustomerMenuChoice::RETURN_TO_MAIN_MENU:
      {
        return;
      }
      case CustomerMenuChoice::PURCHASE_PRODUCT:
      {
        this->purchaseProduct();
        break;
      }
      case CustomerMenuChoice::EDIT_SHOPPING_CART:
      {
        this->viewOrEditShoppingCart();
        break;
      }
      case CustomerMenuChoice::CHECKOUT_AND_PAY:
      {
        break;
      }
      default:
        break;
    }
  }while(choice);
}

void Store::addNewProduct()
{
  bool bError = false;
  do
  {
    auto product = Product::CreateNewProductFromStream(getInputStream());
    if(!product)
    {
      bError = true;
      break;
    }
    if(!this->addProductToInventory(std::move(product)))
    {
      bError = true;
      break;
    }
  }while(0);
  if(bError)
  {
    std::cout << "ERROR!! Something went wrong\n";
  }
  else
  {
    std::cout << "SUCCESSFULLY ADDED PRODUCT\n";
  }
}// addNewProduct()

void Store::deleteProduct()
{
  auto Id = getUint16FromStream(getInputStream());
  if(this->removeProductFromInventory(Id))
  {
    std::cout << "SUCCESSFULLY REMOVED PRODUCT!!\n";
  }
  else
  {
    std::cout << "ERROR REMOVING PRODUCT. PLEASE TRY AGAIN!!\n";
  }
}

void Store::serviceStoreAdmin()
{
  int choice;
  do
  {
    this->displayStoreAdminMenu();
    choice = getIntFromStream(getInputStream());
    switch(StoreAdminChoice(choice))
    {
      case StoreAdminChoice::RETURN_TO_MAIN_MENU:
      {
        return;
      }
      case StoreAdminChoice::ADD_NEW_PRODUCT:
      {
      	this->addNewProduct();
      	break;
      }
      case StoreAdminChoice::DELETE_PRODUCT:
      {
      	this->deleteProduct();
      	break;
      }
      case StoreAdminChoice::VIEW_INVENTORY:
      {
      	this->displayInventory();
      	break;
      }
    } // switch(choice)
  }while(choice);
} // Store::serviceStoreAdmin()
/**
* This is the function that will be called to launch the interactive Menu
* This would be called the Main Menu
* The user can choose an option to get more specific services
* Once done with a request, the user can choose to return to this Main menu
* by selecting '0'.
* Selecting '0' on Main Menu will cause the application to exit.
*/
void Store::launch()
{
  int choice;
  // Stay in the Main Menu until the user chooses to exit the application
  do
  {
    this->displayMainMenu();
    choice = getIntFromStream(getInputStream());
    std::cout<<"You entered:"<<choice<<"\n";
    switch(MainMenuChoice(choice))
    {
      case MainMenuChoice::CUSTOMER:
      {
        this->serviceCustomer();
        break;
      }
      case MainMenuChoice::STORE_ADMIN:
      {
        this->serviceStoreAdmin();
        break;
      }
      default:
        break;
    }
  }while(choice);
}

uint16_t Store::getShoppingCartSize() const
{
  return m_cart->getNumberOfPurchaseOrders();
}

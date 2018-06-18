/** @file Store.cpp
*   @brief This file contains implementation of Store class
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*/

#include "Store.h"
#include "Product.h"
#include "Inventory.h"
#include <iostream>
#include "Helpers.h"

using namespace SuperStore;

uint16_t Store::order_id = 0;

Store::Store(const std::string &name)
    :m_name(name)
{
  m_pInventory = std::make_unique<Inventory>("local");
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

std::unique_ptr<PurchaseOrder> getPurchaseOrderFromStream(std::istream &stream)
{
  do
  {
    std::cout << "enter product id:";
    auto product_id = getUint16FromStream(stream);
    if(!product_id || !this->hasProductById(product_id))
    {
      break;
    }
    uint16_t quantity = 0;
    do
    {
      std::cout << "enter quantity : ";
      quantity = getUint16FromStream(stream);
    }while(!quantity);
    auto sp = m_pInventory->getProductById(product_id);
    if(sp)
    {
      return std::make_unique<PurchasseOrder>(++(this->order_id),
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
    std::cout <<  "Please enter the Id of the product you like to purchase" <<
    "(Enter 0 if you are done) : " ;
    auto product_id = getUint16FromStream(std::cin);
    if(!product_id) { break; }
    std::cout << "Please enter how much quantity you'd like to buy : ";
    uint16_t quantity = 0;
    do
    {
      quantity = getUint16FromStream(std::cin);
    }while(!quantity);
  }while(true);
}
void Store::serviceCustomer()
{
  int choice;
  do
  {
    choice = getIntFromStream(std::cin);
    switch(CustomerMenuChoice(choice))
    {
      case CustomerMenuChoice::RETURN_TO_MAIN_MENU:
      {
        return;
      }
      case CustomerMenuChoice::PURCHASE_PRODUCT:
      {
        break;
      }
      case CustomerMenuChoice::EDIT_SHOPPING_CART:
      {
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
    auto product = Product::CreateNewProductFromStream(std::cin);
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
  auto Id = getUint16FromStream(std::cin);
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
    std::cin >> GetDataFromStream<int>(choice);
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
    std::cin >> GetDataFromStream<int>(choice);
    std::cout<<"You entered:"<<choice<<"\n";
    switch(MainMenuChoice(choice))
    {
    case MainMenuChoice::CUSTOMER:
      this->serviceCustomer();
      break;
    case MainMenuChoice::STORE_ADMIN:
      this->serviceStoreAdmin();
      break;
    default:
      break;
    }
  }while(choice);
}


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

bool Store::addProductToInventory(std::shared_ptr<Product> product)
{
  // if there is already a product in the inventory with the same Id,
  // return false. product cannot be added to the inventory
  if(m_pInventory->hasProductById(product->getID()))
  {
    std::cout<<"ERROR!! Please choose a unique ID for every product\n";
    return false;
  }
  return m_pInventory->addProduct(product);
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
  m_pInventory->displayCatalog();
  std::cout<<"Please enter the id of the product you like to purchase" <<
  "(Enter 0 to return back to MainMenu):";
}

void Store::serviceCustomer()
{
  int choice;
  do
  {
    this->displayCustomerMenu();
    std::cin >> GetDataFromStream<int>(choice);
    if(choice)
    {
      if(m_pInventory->hasProductById(choice))
      {
        /* create order and add to shopping cart */
      }
      else
      {
        std::cout<<"Please enter a valid Product Id\n";
      }
    }
  }while(choice);
}

void Store::addNewProduct()
{
  if(this->addProductToInventory(Product::CreateNewProduct()))
  {
    std::cout << "successfully added product!!\n";
  }
  else
  {
    std::cout << "OOPS!! something went wrong. Please try again!\n";
  }
}

void Store::deleteProduct()
{
  auto Id = Product::getProductIdFromConsole();
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


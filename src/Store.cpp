/** @file Store.cpp
*   @brief This is the Entry point file of the project
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*/

#include "Store.h"
#include "Product.h"
#include "Inventory.h"
#include <iostream>

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

void Store::displayMainMenu() const
{
  std::cout<<"********************************************************************************\n";
  std::cout<<"****************** WELCOME TO " << m_name << " SUPERMARKET ********************************\n";
  std::cout<<"********************************************************************************\n";
  std::cout<<"Please choose an option from below:\n";
  std::cout<<"1)Buy Products\n2)Manage Store\n0)Exit\n";
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
  uint16_t choice = 1;
  while(choice)
  {
    this->displayCustomerMenu();
    std::cin >> choice;
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
  }
}

void Store::serviceStoreAdmin()
{
  uint16_t choice = 1;
  while(choice)
  {
    this->displayStoreAdminMenu();
    std::cin >> choice;
    if(choice)
    {
    }
  }
}
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
  uint16_t choice = 1;
  // Stay in the Main Menu until the user chooses to exit the application
  while(choice)
  {
    this->displayMainMenu();
    std::cin>>choice;
    std::cout<<"You entered:"<<choice<<"\n";
    switch(choice)
    {
    case 1:
      this->serviceCustomer();
      break;
    case 2:
      this->serviceStoreAdmin();
      break;
    default:
      break;
    }
  }
}

#ifdef TEST_SUPER_MARKET
#include "catch.hpp"
TEST_CASE("Validate Store object","[Store]")
{
  Store store("Joe");
  REQUIRE(store.getName() == "Joe");
  REQUIRE(store.getInventorySize() == 0);
}
SCENARIO("Validate addition and removal of Product from Store","[Store]")
{
  GIVEN("A store object")
  {
    Store store("Joes");
    REQUIRE(store.getInventorySize() == 0);
    WHEN("A new product is added to the store")
    {
      store.addProductToInventory(std::make_shared<Product>(20,
							     "Paste",
							     10.76));
      THEN("The Inventory size increases by 1")
      {
        REQUIRE(store.getInventorySize() == 1);
      }
    }
    WHEN("An existing product is removed from inventory")
    {
      store.addProductToInventory(std::make_shared<Product>(20,
							     "Paste",
							     10.76));
      store.removeProductFromInventory(20);
      THEN("The inventory size decreases by 1 ")
      {
        REQUIRE(store.getInventorySize() == 0);
      }
    }
 }
}
#endif

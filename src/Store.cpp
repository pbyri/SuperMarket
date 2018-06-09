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
  if(m_pInventory->hasProductById(product->getID()))
  {
    std::cout<<"ERROR!! Please choose a unique ID for every product\n";
    return false;
  }
  return m_pInventory->addProduct(product);
}

bool Store::removeProductFromInventory(uint16_t id)
{
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
  std::cout<<"1)Buy Products\n2)Manage Store\n";
}
#ifdef TEST_SUPER_MARKET
#include "catch.hpp"
SCENARIO("validate store object","[Store]")
{
  GIVEN("A store object")
  {
    Store store("Joes");
    REQUIRE(store.getName() == "Joes");
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

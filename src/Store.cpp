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

#ifdef TEST_SUPER_MARKET
#include "catch.hpp"
SCENARIO("Store object can be instantiated successfully")
{
auto store = std::make_unique<Store>("Joes");
REQUIRE(store);
REQUIRE(store->getName() == "Joes");
REQUIRE(store->getInventorySize() == 0);
store->addProductToInventory(std::make_shared<Product>(20,
                                                       "Paste",
						       10.76));
REQUIRE(store->getInventorySize() == 1);
store->removeProductFromInventory(20);
REQUIRE(store->getInventorySize() == 0);
}
#endif

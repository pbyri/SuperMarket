/** @file Inventory.cpp
*   @brief Implementation details of the Inventory
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*
*   This file contains the implementation details of Inventory class and also
*   contains unit test cases for Inventory class.
*/
#include "Inventory.h"
#include <iostream>
#include "Product.h"
#include "assert.h"

using namespace SuperStore;

Inventory::Inventory(const std::string &name) : m_name(name)
{
}

bool Inventory::addProduct(std::shared_ptr<Product> product)
{
  // if the inventory already has a product with the given Id, return false
  // Otherwise, add the product to the catalog and return true
  if(hasProductById(product->getID()))
  {
    return false;
  }
  m_catalog[product->getID()] = product;
  return true;
}

// If the inventory has a product with the give id, remove it from the catalog
// and return
void Inventory::removeProduct(uint16_t product_id)
{
  if(hasProductById(product_id))
  {
    m_catalog.erase(product_id);
  }
}

void Inventory::displayCatalog() const
{
  if(!getProductCount())
  {
    std::cout<<"Sorry, the inventory is empty. Please contact store manager\n";
    return;
  }
  std::cout<<"================================================================\n";
  std::cout<<"ProductID     Description                         Price\n";
  std::cout<<"================================================================\n";
}

// check the catalog for a product with given Id. if found, return true.
// Otherwise return false.
bool Inventory::hasProductById(uint16_t id) const
{
  if(m_catalog.find(id) != m_catalog.end())
  {
    return true;
  }
  return false;
}

// if the inventory has a product with the given Id, return a pointer to the
// Product object. Otherwise, return nullptr
const Product* Inventory::getProductById(uint16_t id) 
{
 assert(this->hasProductById(id));

 if(this->hasProductById(id))
 {
   return m_catalog[id].get();
 }
 return nullptr;
}

// return the size of the catalog as the size of the Inventory
uint16_t Inventory::getProductCount() const
{
  return m_catalog.size();
}

Inventory::~Inventory()
{
}



#ifdef TEST_SUPER_MARKET
#include "catch.hpp"
TEST_CASE("validate Inventory Object","[Inventory]")
{
  Inventory i("local");
  REQUIRE(i.getName() == "local");
  REQUIRE(i.getProductCount() == 0);
}
SCENARIO("validate Inventory Object", "[Inventory]")
{
  GIVEN("An Inventory Object")
  {
    Inventory catalog("local");
    REQUIRE(catalog.getProductCount() == 0);
    WHEN("A new prduct is added to the Inventory")
    {
      catalog.addProduct(std::make_shared<Product>(10,"soap",1.2));
      THEN("product count of inventory increases by 1")
      {
        REQUIRE(catalog.getProductCount() == 1);
      }
    }
    WHEN("An existing product is removed from Inventory")
    {
      catalog.addProduct(std::make_shared<Product>(20,"belt",14));
      catalog.removeProduct(20);
      THEN("product count decreases by 1")
      {
        REQUIRE(catalog.getProductCount() == 0);
      }
    }
  }
}
#endif

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
  //assert(hasProductById(product->getID());
  if(hasProductById(product->getID()))
  {
    return false;
  }
  m_catalog[product->getID()] = product;
  return true;
}

void Inventory::removeProduct(uint16_t product_id)
{
  if(hasProductById(product_id))
  {
    m_catalog.erase(product_id);
  }
}

void Inventory::displayCatalog() const
{
  std::cout<<"================================================================\n";
  std::cout<<"ProductID     Description                         Price\n";
  std::cout<<"================================================================\n";
}

bool Inventory::hasProductById(uint16_t id) const
{
  if(m_catalog.find(id) != m_catalog.end())
  {
    return true;
  }
  return false;
}

const Product* Inventory::getProductById(uint16_t id) 
{
 assert(this->hasProductById(id));

 if(this->hasProductById(id))
 {
   return m_catalog[id].get();
 }
 return nullptr;
}

uint16_t Inventory::getProductCount() const
{
  return m_catalog.size();
}

Inventory::~Inventory()
{
}



#ifdef TEST_SUPER_MARKET
#include "catch.hpp"
SCENARIO("catalog object instantiation is successfu")
{
  auto catalog = std::make_unique<Inventory>("Joes");
  REQUIRE(catalog);
  REQUIRE(catalog->getName().compare("Joes") == 0);
  REQUIRE(catalog->getProductCount() == 0);
  REQUIRE(catalog->addProduct(std::make_shared<Product>(10,"soap",1.2)));
  REQUIRE(catalog->getProductCount() == 1);
  catalog->removeProduct(10);
  REQUIRE(catalog->getProductCount() == 0);
}
#endif

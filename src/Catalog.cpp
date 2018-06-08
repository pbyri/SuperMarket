#include "Catalog.h"
#include <iostream>
#include "Product.h"
#include "assert.h"

using namespace SuperStore;

Catalog::Catalog(const std::string &name) : m_name(name)
{
}


bool Catalog::addProduct(std::shared_ptr<Product> product)
{
  //assert(hasProductById(product->getID());
  if(hasProductById(product->getID()))
  {
    return false;
  }
  m_inventory[product->getID()] = product;
  return true;
}

void Catalog::removeProduct(uint16_t product_id)
{
  if(hasProductById(product_id))
  {
    m_inventory.erase(product_id);
  }
}

void Catalog::displayInventory() const
{
  std::cout<<"================================================================\n";
  std::cout<<"ProductID     Description                         Price\n";
  std::cout<<"================================================================\n";
}

bool Catalog::hasProductById(uint16_t id) const
{
  if(m_inventory.find(id) != m_inventory.end())
  {
    return true;
  }
  return false;
}

const Product* Catalog::getProductById(uint16_t id) 
{
 assert(this->hasProductById(id));

 if(this->hasProductById(id))
 {
   return m_inventory[id].get();
 }
 return nullptr;
}

uint16_t Catalog::getProductCount() const
{
  return m_inventory.size();
}

Catalog::~Catalog()
{
}



#ifdef TEST_SUPER_MARKET
#include "catch.hpp"
SCENARIO("catalog object instantiation is successfu")
{
  auto catalog = std::make_unique<Catalog>("Joes");
  REQUIRE(catalog);
  REQUIRE(catalog->getName().compare("Joes") == 0);
  REQUIRE(catalog->getProductCount() == 0);
  REQUIRE(catalog->addProduct(std::make_shared<Product>(10,"soap",1.2)));
  REQUIRE(catalog->getProductCount() == 1);
  catalog->removeProduct(10);
  REQUIRE(catalog->getProductCount() == 0);
}
#endif

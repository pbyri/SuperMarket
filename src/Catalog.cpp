#include "Catalog.h"
#include <iostream>
#include "Product.h"

using namespace SuperStore;

Catalog::Catalog(const std::string &name) : m_name(name)
{
}


bool Catalog::addProductToInventory(std::unique_ptr<Product> product)
{
  return true;
}

bool Catalog::removeProductFromInventory(uint16_t product_id)
{
  return true;
}

void Catalog::displayInventory() const
{
  std::cout<<"================================================================\n";
  std::cout<<"ProductID     Description                         Price\n";
  std::cout<<"================================================================\n";
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
}
#endif

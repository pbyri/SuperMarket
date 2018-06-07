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
  std::cout<<"displaying inventory\n";
}

Catalog::~Catalog()
{
}

#if 0
#include <memory>
int main()
{
  auto catalog = std::make_unique<Catalog>("pavan");
  std::cout<<"catalog name:" << catalog->getName() << "\n";
  return 0;
}
#endif

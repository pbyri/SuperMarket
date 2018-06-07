#include "Product.h"

using namespace SuperStore;

Product::Product(uint16_t id, const std::string &description, double price)
    :m_id(id),
    m_description(description),
    m_price(price)
{
}

Product::~Product()
{
}

#if 0
#include <memory>
#include <iostream>
int main()
{
  auto product = std::make_unique<Product>(10,"soap",2.35);
  std::cout<<"Product ID:" << product->getID() << "\n";
  std::cout<<"Description:"<<product->getDescription()<<"\n";
  std::cout<<"Price:"<<product->getPrice()<<"\n";
return 0;
}
#endif


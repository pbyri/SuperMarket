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


#ifdef TEST_SUPER_MARKET
#include "catch.hpp"
#include <memory>
SCENARIO("validate creation of Product object")
{
  auto product = std::make_shared<Product>(10,"soap",2.35);
  REQUIRE(product->getID() == 10);
  REQUIRE(product->getDescription() == "soap");
  REQUIRE(product->getPrice() == 2.35);

}
#endif

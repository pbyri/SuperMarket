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
SCENARIO("validate Product object", "[product]")
{
  Product p(10,"soap",2.35);
  REQUIRE(p.getID() == 10);
  REQUIRE(p.getDescription() == "soap");
  REQUIRE(p.getPrice() == 2.35);

}
#endif

/** @file ProductTest.cpp
*   @brief This file contains unit tests for Product.cpp
*   @author Pavan Kumar Byri
*   @date 06-13-2018
*
*/

#include "Product.h"
#include "catch.hpp"
#include <memory>

using namespace SuperStore;

SCENARIO("validate Product object", "[product]")
{
  Product p(10,"soap",2.35);
  REQUIRE(p.getID() == 10);
  REQUIRE(p.getDescription() == "soap");
  REQUIRE(p.getPrice() == 2.35);

}

/** @file ProductTest.cpp
*   @brief This file contains unit tests for Product.cpp
*   @author Pavan Kumar Byri
*   @date 06-13-2018
*
*/

#include "Product.h"
#include "catch.hpp"
#include <memory>
#include <sstream>

using namespace SuperStore;

SCENARIO("validate Product object", "[Product]")
{
  Product p(10,"soap",2.35);
  REQUIRE(p.getID() == 10);
  REQUIRE(p.getDescription() == "soap");
  REQUIRE(p.getPrice() == 2.35);

}

SCENARIO("Test getProductIdFromStream","[Product]")
{
  std::istringstream iss;
  iss.str("-1\n10\nname\n3.33\n"); 
  auto product = Product::CreateNewProductFromStream(iss);
  //Negative values are not valid.
  REQUIRE(product);
  REQUIRE(10 == product->getID());
  iss.str("75534\n220\nname\n2.22\n");
  product = Product::CreateNewProductFromStream(iss);
  //values higher than uint16_max are invalid
  REQUIRE(220 == product->getID());
}

//TODO add trim cases after implementing
SCENARIO("Test getProductDescriptionFromStream","[Product]")
{
  std::istringstream iss;
  iss.str("10\n\n\n\nname\n2.22\n"); // empty name is not valid
  auto product = Product::CreateNewProductFromStream(iss);
  REQUIRE("name" == product->getDescription());
}

SCENARIO("Test getProductPriceFromStream", "[Product]")
{
  std::istringstream iss;
  iss.str("12\nname\n-20.77\n10.22\n"); // negatibve price is not allowed
  auto product = Product::CreateNewProductFromStream(iss);
  REQUIRE(10.22 == product->getPrice());
  iss.str("12\nname\n0\n10.22\n"); // zero is not a valid price
  product = Product::CreateNewProductFromStream(iss);
  REQUIRE(10.22 == product->getPrice());
  iss.str("12\nname\n10\n"); // An integer number is a valid double
  product = Product::CreateNewProductFromStream(iss);
  REQUIRE(10 == product->getPrice());
}

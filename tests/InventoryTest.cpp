/** @file InventoryTest.cpp
*   @brief This file contains all unit tests for Inventory.cpp
*   @author Pavan Kumar Byri
*   @date 06-13-2018
*
*/
#include "Product.h"
#include "Inventory.h"
#include "catch.hpp"

using namespace SuperStore;

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

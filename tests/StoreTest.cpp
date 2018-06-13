/** @file StoteTest.cpp
*   @brief This file contains unit tests for Store.cpp
*   @author Pavan Kumar Byri
*   @date 06-13-2018
*
*/

#include "Product.h"
#include "Store.h"
#include "catch.hpp"

using namespace SuperStore;

TEST_CASE("Validate Store object","[Store]")
{
  Store store("Joe");
  REQUIRE(store.getName() == "Joe");
  REQUIRE(store.getInventorySize() == 0);
}
SCENARIO("Validate addition and removal of Product from Store","[Store]")
{
  GIVEN("A store object")
  {
    Store store("Joes");
    REQUIRE(store.getInventorySize() == 0);
    WHEN("A new product is added to the store")
    {
      store.addProductToInventory(std::make_shared<Product>(20,
							     "Paste",
							     10.76));
      THEN("The Inventory size increases by 1")
      {
        REQUIRE(store.getInventorySize() == 1);
      }
    }
    WHEN("An existing product is removed from inventory")
    {
      store.addProductToInventory(std::make_shared<Product>(20,
							     "Paste",
							     10.76));
      store.removeProductFromInventory(20);
      THEN("The inventory size decreases by 1 ")
      {
        REQUIRE(store.getInventorySize() == 0);
      }
    }
 }
}

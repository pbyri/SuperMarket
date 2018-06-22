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
      catalog.addProduct(std::make_unique<Product>(10,"soap",1.2));
      THEN("product count of inventory increases by 1")
      {
        REQUIRE(catalog.getProductCount() == 1);
      }
    }
    WHEN("An existing product is removed from Inventory")
    {
      catalog.addProduct(std::make_unique<Product>(20,"belt",14));
      catalog.removeProduct(20);
      THEN("product count decreases by 1")
      {
        REQUIRE(catalog.getProductCount() == 0);
      }
    }
    WHEN("If same product is added again, inventory size remains same")
    {
      catalog.addProduct(std::make_unique<Product>(20,"belt",14));
      auto size = catalog.getProductCount();
      catalog.addProduct(std::make_unique<Product>(20,"belt",14));
      THEN("product count decreases by 1")
      {
        REQUIRE(size == catalog.getProductCount());
      }
    }
    WHEN("getProductById is invoked")
    {
      auto product = std::make_unique<Product>(20,"belt",14);
      const Product *ptr = product.get();
      catalog.addProduct(std::move(product));
      auto shared = catalog.getProductById(20);
      THEN("it should return the original product object")
      {
        REQUIRE(ptr == shared.get());
      }
    }
    WHEN("getProductById on non existing product")
    {
      auto shared = catalog.getProductById(1);
      REQUIRE(!shared);
    }
  }
}

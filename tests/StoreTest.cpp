/** @file StoteTest.cpp
*   @brief This file contains unit tests for Store.cpp
*   @author Pavan Kumar Byri
*   @date 06-13-2018
*
*/

#include "Product.h"
#include "ShoppingCart.h"
#include "Store.h"
#include "catch.hpp"
#include <sstream>

using namespace SuperStore;

TEST_CASE("Validate Store object","[Store]")
{
  Store store("Joe");
  REQUIRE(store.getName() == "Joe");
  REQUIRE(store.getInventorySize() == 0);
}

TEST_CASE("validate getPurchaseOrderFromStream", "[Store]")
{
  std::istringstream ss;
  InStreamHolder ish(ss);
  Store store("Joes",ish);
  ss.str("0\n");
  REQUIRE(!(store.getPurchaseOrderFromStream()));
  ss.str("10\n");
  REQUIRE(!(store.getPurchaseOrderFromStream()));
  store.addProductToInventory(std::make_unique<Product>(20,
               "Paste",
               10.76));
  ss.str("20\n3\n");
  auto order = store.getPurchaseOrderFromStream();
  REQUIRE(order->getOrderNumber() == 1);
  REQUIRE(order->getCost() == 10.76*3);
  REQUIRE(order->getQuantity() == 3);
}

TEST_CASE("validate purchaseProduct method","[Store]")
{
  std::istringstream ss;
  InStreamHolder ish(ss);
  Store store("Joes",ish);
  store.addProductToInventory(std::make_unique<Product>(20,
               "Paste",
               10.76));
  ss.str("20\n3\n0\n");
  REQUIRE(store.getShoppingCartSize() == 0);
  store.purchaseProduct();
  REQUIRE(store.getShoppingCartSize() == 1);
}

SCENARIO("Validate addition and removal of Product from Store","[Store]")
{
  GIVEN("A store object")
  {
    std::istringstream ss;
    InStreamHolder ish(ss);
    Store store("Joes",ish);
    REQUIRE(store.getInventorySize() == 0);
    WHEN("A new product is added to the store")
    {
      store.addProductToInventory(std::make_unique<Product>(20,
							     "Paste",
							     10.76));
      THEN("The Inventory size increases by 1")
      {
        REQUIRE(store.getInventorySize() == 1);
      }
    }
    WHEN("An existing product is removed from inventory")
    {
      store.addProductToInventory(std::make_unique<Product>(20,
							     "Paste",
							     10.76));
      store.removeProductFromInventory(20);
      THEN("The inventory size decreases by 1 ")
      {
        REQUIRE(store.getInventorySize() == 0);
      }
    }
    WHEN("same product is added twice")
    {
      store.addProductToInventory(std::make_unique<Product>(20,
                   "Paste",
                   10.76));
      store.addProductToInventory(std::make_unique<Product>(20,
                   "Paste",
                   10.76));
      THEN("The Inventory size increases only once")
      {
        REQUIRE(store.getInventorySize() == 1);
      }
    }
    WHEN("A non existing product is tried to be removed")
    {
      THEN("the method should return false")
      REQUIRE(false == store.removeProductFromInventory(20));
    }
    WHEN("deleteOrder is called on valid order")
    {
      store.addProductToInventory(std::make_unique<Product>(20,
                   "Paste",
                   10.76));
      ss.str("20\n3\n0\n");
      REQUIRE(store.getShoppingCartSize() == 0);
      store.purchaseProduct();
      REQUIRE(store.getShoppingCartSize() == 1);
      ss.str("1\n");
      store.deleteOrder();
      THEN("Shopping Cart size goes down by 1")
      {
        REQUIRE(store.getShoppingCartSize() == 0);
      }
    }
    WHEN("update order is called on valid order_id")
    {
      store.addProductToInventory(std::make_unique<Product>(20,
                   "Paste",
                   10.76));
      ss.str("20\n3\n0\n");
      REQUIRE(store.getShoppingCartSize() == 0);
      store.purchaseProduct();
      REQUIRE(store.getShoppingCartSize() == 1);
      ss.str("1\n7\n0\n");
      store.updateOrder();
      THEN("Shopping Cart size does not change")
      {
        REQUIRE(store.getShoppingCartSize() == 1);
      }
    }
 }
}

SCENARIO("validate operations on shopping cart","[Store]")
{
  GIVEN("A store with a shopping cart containing 2 orders")
  {
    std::istringstream ss;
    InStreamHolder ish(ss);
    Store store("Joes",ish);
    store.addProductToInventory(std::make_unique<Product>(20,
		 "Paste",
		 10.76));
    store.addProductToInventory(std::make_unique<Product>(21,
		 "book",
		 14.76));
    REQUIRE(store.getShoppingCartSize() == 0);
    ss.str("20\n4\n21\n6\n0\n");
    store.purchaseProduct();
    REQUIRE(store.getShoppingCartSize() == 2);
    WHEN("return to main menu is selected on view/edit cart menu")
    {
      ss.str("0\n");
      store.viewOrEditShoppingCart();
      THEN("shopping cart size does not change")
      {
        REQUIRE(store.getShoppingCartSize() == 2);
      }
    }
    WHEN("update order is selected on existing order")
    {
      ss.str("2\n1\n2\n0\n0\n");
      store.viewOrEditShoppingCart();
      THEN("shopping cart size does not change")
      {
        REQUIRE(store.getShoppingCartSize() == 2);
      }
    }
    WHEN("delete order is selected on existing order")
    {
      ss.str("1\n2\n0\n0\n");
      store.viewOrEditShoppingCart();
      THEN("Shopping Cart size reduces by 1")
      {
        REQUIRE(store.getShoppingCartSize() == 1);
      }
    }
    WHEN("addNewProduct is called")
    {
      auto cart_size = store.getShoppingCartSize();
      auto inv_size = store.getInventorySize();
      REQUIRE(cart_size == 2);
      REQUIRE(inv_size == 2);
      ss.str("30\ncap\n3.55\n0\n");
      store.addNewProduct();
      THEN("inventory size goes up by 1")
      {
        REQUIRE(store.getShoppingCartSize() == cart_size);
	REQUIRE(store.getInventorySize() == inv_size + 1);
      }
    }
    WHEN("deleteProduct is called on existing product")
    {
      auto cart_size = store.getShoppingCartSize();
      auto inv_size = store.getInventorySize();
      REQUIRE(cart_size == 2);
      REQUIRE(inv_size == 2);
      ss.str("20\n");
      store.deleteProduct();
      THEN("inventory size down by 1")
      {
        REQUIRE(store.getShoppingCartSize() == cart_size);
	REQUIRE(store.getInventorySize() == inv_size - 1);
      }
    }
  }
}

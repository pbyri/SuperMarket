/** @file ShoppingCartTest.cpp
*   @brief This file contains unit tests for ShoppingCart.cpp
*   @author Pavan Kumar Byri
*   @date 06-13-2018
*
*/

#include "Product.h"
#include "ShoppingCart.h"
#include <string>
#include "catch.hpp"
#include <sstream>

using namespace SuperStore;

TEST_CASE("verify PurchaseOrder object creation","[PurchaseOrder]")
{
  auto product = std::make_shared<Product>(10,"pen",3.33);
  auto order = std::make_unique<PurchaseOrder>(12254,
					      product,
                                              3);
  REQUIRE(order);
  REQUIRE(order.get());
  REQUIRE(order->getOrderNumber() == 12254);
  REQUIRE(order->getCost() == 3 * 3.33);
}
TEST_CASE("verify ShoppingCart object creation","[ShoppingCart]")
{
  auto cart = std::make_unique<ShoppingCart>();

  REQUIRE(cart);
  REQUIRE(cart.get());
  REQUIRE(cart->getNumberOfPurchaseOrders() == 0);
}
SCENARIO("verify adding and removing purchase order to/from the cart",\
         "[ShoppingCart]")
{
  GIVEN("A ShoppingCart")
  {
    std::istringstream ss;
    InStreamHolder ish(ss);
    auto cart = std::make_unique<ShoppingCart>(ish);
    REQUIRE(cart.get());
    REQUIRE(cart->getNumberOfPurchaseOrders() == 0);
    REQUIRE(!(cart->getPurchaseOrderById(1)));
    WHEN("A purchase order is added to the cart")
    {
      auto product = std::make_shared<Product>(10,"pen",3.33);
      auto order = std::make_unique<PurchaseOrder>(12254,
						  product,
                                                  3);
      REQUIRE(order.get());
      cart->addToCart(std::move(order));
      THEN("Shopping cart size increases by 1")
      {
        REQUIRE(cart->getNumberOfPurchaseOrders() == 1);
      }
    }
    WHEN("When a PurchaseOrder is removed from the cart")
    {
      auto product = std::make_shared<Product>(10,"pen",3.33);
      auto order = std::make_unique<PurchaseOrder>(12254,
						  product,
                                                  3);
      REQUIRE(order.get());
      REQUIRE(cart->getNumberOfPurchaseOrders() == 0);
      auto order_num = order->getOrderNumber();
      cart->addToCart(std::move(order));
      cart->removeFromCart(order_num);
      THEN("The size of the cart goes down by 1")
      {
        REQUIRE(cart->getNumberOfPurchaseOrders() == 0);
      }
    }
    WHEN("When a PurchaseOrder is updated")
    {
      auto product = std::make_shared<Product>(10,"pen",3.33);
      auto order = std::make_unique<PurchaseOrder>(12254,
						  product,
                                                  3);
      REQUIRE(order.get());
      REQUIRE(cart->getNumberOfPurchaseOrders() == 0);
      auto order_num = order->getOrderNumber();
      cart->addToCart(std::move(order));
      ss.str("\n12254\n6\n0\n");
      cart->updateOrder();
      THEN("The updates reflect in the purchase order")
      {
        REQUIRE(order_num == 12254);
        REQUIRE(cart->getPurchaseOrderById(order_num));
        REQUIRE(cart->getPurchaseOrderById(order_num)->getQuantity() == 6);

      }
    }
    WHEN("product is removed from inventory")
    {
      auto product = std::make_shared<Product>(10,"pen",3.33);
      auto order = std::make_unique<PurchaseOrder>(1,product,3);
      REQUIRE(order->getCost() == 3*3.33);
      product.reset();
      THEN("The getCost returns 0")
      {
        REQUIRE(order->getCost() == 0);
      }
    }
    WHEN("same purchase order_id is added twice to the cart")
    {
      auto product = std::make_shared<Product>(10,"pen",3.33);
      auto order = std::make_unique<PurchaseOrder>(12254,
              product,
                                                  3);
      auto order2 = std::make_unique<PurchaseOrder>(12254,
              product,
                                                  3);
      REQUIRE(cart->getNumberOfPurchaseOrders() == 0);
      cart->addToCart(std::move(order));
      cart->addToCart(std::move(order2));
      THEN("Only one purchase order gets added")
      {
        REQUIRE(cart->getNumberOfPurchaseOrders() == 1);
      }
    }
  }
}

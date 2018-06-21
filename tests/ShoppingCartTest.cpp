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
    ss.str("");
    InStreamHolder ssh(ss);
    auto cart = std::make_unique<ShoppingCart>(ssh);
    REQUIRE(cart.get());
    REQUIRE(cart->getNumberOfPurchaseOrders() == 0);
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
      ss.str("1\n6\n");
      cart->updateOrder();
      THEN("The updates reflect in the purchase order")
      {
        REQUIRE(cart->getPurchaseOrderById(order_num));
        REQUIRE(cart->getPurchaseOrderById(order_num)->getQuantity() == 6);
      }
    }
  }
}

/** @file ShoppingCart.cpp
*   @brief This file provides implementation for PurchaseOrder and
*   Shoppingcart classes and also provides unit tests for the above
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*/

#include "Product.h"
#include "ShoppingCart.h"
#include <algorithm>

using namespace SuperStore;

PurchaseOrder::PurchaseOrder(uint16_t order_number,
                            std::shared_ptr<Product> product,
			    uint16_t quantity)
    :m_orderNumber(order_number),
    m_pProduct(product),
    m_quantity(quantity)
{
}

PurchaseOrder::~PurchaseOrder()
{
}

/**
* cost of the order is calculated as 
* cost = price of the product * quantity
*/
double PurchaseOrder::getCost() const
{
  return this->m_pProduct->getPrice() * this->m_quantity;
}

uint16_t PurchaseOrder::getOrderNumber() const
{
  return m_orderNumber;
}

ShoppingCart::ShoppingCart()
{
}

ShoppingCart::~ShoppingCart()
{
}

void ShoppingCart::addToCart(std::unique_ptr<PurchaseOrder> order)
{
  // try to find a PurchaseOrder with same order
  auto it = std::find_if(m_orders.begin(),
                         m_orders.end(),
                         [&order](auto &order_) { 
			 return order->getOrderNumber() == 
			 order_->getOrderNumber(); 
			 }
			);
  // if not found, then add the purchase order to the vector
  // this is to ensure purchase order_id's are unique in the cart
  if(it == m_orders.end())
  {
    m_orders.push_back(std::move(order));
  }
}

void ShoppingCart::removeFromCart(uint16_t order_id)
{
  // Erase all PurchaseOrders with order_id
  m_orders.erase(std::remove_if(m_orders.begin(),
                               m_orders.end(),
                               [&order_id](auto &order) { 
			       return order->getOrderNumber() == order_id; 
			       }
                               ),
                m_orders.end()
                );
}

uint16_t ShoppingCart::getNumberOfPurchaseOrders() const
{
  return m_orders.size();
}


#ifdef TEST_SUPER_MARKET
#include "catch.hpp"

TEST_CASE("verify PurchaseOrder object creation","[PurchaseOrder]")
{
  auto order = std::make_unique<PurchaseOrder>(12254,
                                              std::make_shared<Product>(10,
                                                                       "pen",
                                                                       3.33),
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
    auto cart = std::make_unique<ShoppingCart>();
    REQUIRE(cart.get());
    REQUIRE(cart->getNumberOfPurchaseOrders() == 0);
    WHEN("A purchase order is added to the cart")
    {
      auto order = std::make_unique<PurchaseOrder>(12254,
                                                  std::make_shared<Product>(10,
                                                                           "pen",
                                                                           3.33),
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
      auto order = std::make_unique<PurchaseOrder>(12254,
                                                  std::make_shared<Product>(10,
                                                                           "pen",
                                                                           3.33),
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
  }
}
#endif

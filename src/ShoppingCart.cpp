/** @file ShoppingCart.cpp
*   @brief This file provides implementation for PurchaseOrder and
*   Shoppingcart classes 
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*/

#include "Product.h"
#include "ShoppingCart.h"
#include <algorithm>
#include <iostream>
#include "assert.h"

using namespace SuperStore;

PurchaseOrder::PurchaseOrder(uint16_t order_number,
                            std::weak_ptr<Product> product,
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
  auto product = m_pProduct.lock();
  if(product)
  {
    return product->getPrice() * this->m_quantity;
  }
  return 0;
}

uint16_t PurchaseOrder::getOrderNumber() const
{
  return m_orderNumber;
}

void PurchaseOrder::display() const
{
  auto sp = m_pProduct.lock();
  if(sp)
  {
    std::cout << m_orderNumber << " " << sp->getDescription() << "  " <<
    this->m_quantity << " " << this->getCost() << std::endl;
  }
}

void PurchaseOrder::updateQuantity(uint16_t quantity)
{
  assert(quantity);
  m_quantity = quantity;
}

ShoppingCart::ShoppingCart(InStreamHolder &stream)
    :m_iStream(stream)
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

void ShoppingCart::updateOrder()
{
  uint16_t order_id;
  do
  {
    std::cout << "Please enter the order id you want to update : ";
    order_id = getUint16FromStream(m_iStream);
    auto iter = std::find_if(m_orders.begin(),
                             m_orders.end(),
                             [order_id](auto &order_) {
                             return order_->getOrderNumber() == order_id;
                             }
                            );
   if(iter != m_orders.end())
   {
     uint16_t quantity = 0;
     do
     {
       std::cout << "Enter new quantity : ";
       quantity = getUint16FromStream(m_iStream);
     }while(!quantity);
     (*iter)->updateQuantity(quantity);
   }
  }while(order_id);
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

void ShoppingCart::display() const
{
  double total_cost = 0;
  std::cout << "====================================================\n";
  std::cout << "Order ID" << "  " << "Description" << " " <<
  "Quantity" << " " << "Cost" << "\n";
  std::cout << "====================================================" << 
  std::endl;
  std::for_each(m_orders.begin()
               , m_orders.end()
               ,[&total_cost](auto &order) { 
                             order->display();
                             total_cost += order->getCost();
                             }
               ); 
  std::cout << "Total Cost : " << total_cost << std::endl;
}

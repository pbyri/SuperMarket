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
  m_orders.push_back(std::move(order));
}

void ShoppingCart::removeFromCart(uint16_t order_id)
{
  std::remove_if(m_orders.begin(),
                 m_orders.end(),
		 [order_id](auto &order) { return order->getOrderNumber() == order_id; }
		 );
}

#include "PurchaseOrder.h"

using namespace SuperStore;

PurchaseOrder::PurchaseOrder(std::shared_ptr<Product> product,
                             uint16_t  quantity)
    :m_pProduct(product),
    m_quantity(quantity)
{
}

PurchaseOrder::~PurchaseOrder()
{
}


double PurchaseOrder::getCost() const
{
  return m_pProduct->getPrice() * m_quantity;
}



#ifndef SUPERMARKET_SHOPPING_CART_H
#define SUPERMARKET_SHOPPING_CART_H

#include <vector>
#include <memory>

namespace SuperStore
{
  /*!< Pre-declarations */
  class Product;
  /**PurchaseOrder class
  *  This class represents one purchase order
  */
  class PurchaseOrder
  {
  public:
    /** Consntructor
    */
    PurchaseOrder(uint16_t order_num,
                  std::shared_ptr<Product> prodiuct,
                  uint16_t quantity);
    /** getCost method
    *   This method returns the cost of this order
    */
    double getCost() const;
    /** getOrderNumber method
    *   This method returns the order number for this PurchaseOrder
    */
    uint16_t getOrderNumber() const;
    /** Destructor
    */
    ~PurchaseOrder();
  private:
    std::shared_ptr<Product> m_pProduct; /*!< Product being purchased */ /*!< Product being purchased */
    uint16_t m_quantity; /*!< number of instances of Product purchased */
    uint16_t m_orderNumber; /*!< unique number for the purchase order */
  };
  /** ShoppingCart class
  *   This class represents the shopping cart for a customer
  */
  class ShoppingCart
  {
  public:
    /** Constructor
    */
    ShoppingCart();
    /** addToCart method
    *   This method is used to add a PurchaseOrder to the cart
    */
    void addToCart(std::unique_ptr<PurchaseOrder> order);
    /** removeFromCart method
    *   This method is used to remove a specific PurchaseOrder from the ShoppingCart
    */
    void removeFromCart(uint16_t order_id);
    /** Destructor
    */
    ~ShoppingCart();
  private:
    std::vector<std::unique_ptr<PurchaseOrder>> m_orders;
  };
}
#endif

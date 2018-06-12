/** @file ShoppingCart.h
*   @brief This file contains the prototype and interfaces for PurchaseOrder
*   and ShoppingCart classes
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*/

#ifndef SUPERMARKET_SHOPPING_CART_H
#define SUPERMARKET_SHOPPING_CART_H

#include <vector>
#include <memory>

/** @brief namespace SuperStore encapsulates all definitions for SuperMarket
*/
namespace SuperStore
{
  /*!< Forward Declarations */
  class Product;
  /** @brief  class PurchaseOrder: prototypes a PurchaseOrder
  *
  *  This class represents one purchase order. One PurchaseOrder pertains to
  *  one particular product and a specific quantity and is identified by a
  *  unique Id.
  *
  */
  class PurchaseOrder
  {
  public:
    /** @brief Constructor with 3 arguments
    *   @param[in] order_num A unique Id to identify  this PurchaseOrder
    *   @param[in] product A shared_ptr of Product type that is tied to this
    *   PurchaseOrder
    *   @param[in] quantity The number of instances of product being purchased.
    */
    PurchaseOrder(uint16_t order_num,
                  std::shared_ptr<Product> prodiuct,
                  uint16_t quantity);
    /** @brief return the cost of this PurchaseOrder
    *   @return double
    *
    *   This method returns the cost of this order as (quantity * price)
    *
    */
    double getCost() const;
    /** @brief return the order number for this PurchaseOrder
    *   @return uint16_t
    *
    *   This method returns the unique order number for this PurchaseOrder
    *
    */
    uint16_t getOrderNumber() const;
    /** Destructor
    */
    ~PurchaseOrder();
  private:
    std::shared_ptr<Product> m_pProduct; /*!< Product being purchased */ 
    uint16_t m_quantity; /*!< number of instances of Product purchased */
    uint16_t m_orderNumber; /*!< unique number for the purchase order */
  };

  /** @brief class ShoppingCart: prototypes the shopping cart
  *
  *   This class represents the collection of products the customer is 
  *   interested in purchasing similar to a shopping bag.
  *
  */
  class ShoppingCart
  {
  public:
    /** @brief Default Constructor
    */
    ShoppingCart();
    /** @brief add a PuchaseOrder to the ShoppingCart
    *   @param[in] order A shared_ptr of type PurchaseOrder that needs to be 
    *   added to the cart.
    *   @return void
    */
    void addToCart(std::unique_ptr<PurchaseOrder> order);
    /** @brief remove an existing PurchaseOrder from the ShoppingCart
    *   @param[in] order_id unique Id that identifies a PurchaseOrder
    *   @return void
    *   This method is used to remove a specific PurchaseOrder from the 
    *   ShoppingCart
    */
    void removeFromCart(uint16_t order_id);
    /** @brief returns number of purchase orders in the ShoppingCart
    *   @return uint16_t
    *
    *   This method returns the number of purchase orders in the cart
    *
    */
    uint16_t getNumberOfPurchaseOrders() const;
    /** Destructor
    */
    ~ShoppingCart();
  private:
    /** @brief a vector of purchase orders
    */
    std::vector<std::unique_ptr<PurchaseOrder>> m_orders;
  };
}
#endif

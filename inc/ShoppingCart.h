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
#include "Helpers.h"
#include "StreamWrapper.h"

/** @brief namespace SuperStore encapsulates all definitions for SuperMarket
*/
namespace SuperStore
{
  /*!< Forward Declarations */
  class Product;
  class ShoppingCart;
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
    /// @brief a friend class of PurchaseOrder
    friend class ShoppingCart;
    /** @brief Constructor with 3 arguments
    *   @param[in] order_num A unique Id to identify  this PurchaseOrder
    *   @param[in] product A weak_ptr of Product type that is tied to this
    *   PurchaseOrder
    *   @param[in] quantity The number of instances of product being purchased.
    */
    PurchaseOrder(uint16_t order_num,
                  std::weak_ptr<Product> prodiuct,
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
    /** @brief This method displays a PurchaseOrder in human readable form
    *   @return void
    */
    /** @brief returns the quantity of this purchase order
    *   @return uint16_t
    */
    uint16_t getQuantity() const;
    void display() const;
    /** Destructor
    */
    ~PurchaseOrder();
  private:
    std::weak_ptr<Product> m_pProduct; /*!< Product being purchased */ 
    uint16_t m_quantity; /*!< number of instances of Product purchased */
    uint16_t m_orderNumber; /*!< unique number for the purchase order */

    /** @bried update the quantity field of the PurchaseOrder
    *   @param[in] quantity The new quantity for this order
    *   @return void
    */
    void updateQuantity(uint16_t quantity);
  };

  /** @brief class ShoppingCart: prototypes the shopping cart
  *
  *   This class represents the collection of products the customer is 
  *   interested in purchasing similar to a shopping bag.
  *
  */
  class ShoppingCart : public InStreamWrapper
  {
  public:
    /** @brief Default Constructor
    */
    ShoppingCart(InStreamHolder &stream = cin_holder());
    /** @brief add a PuchaseOrder to the ShoppingCart
    *   @param[in] order A unique_ptr of type PurchaseOrder that needs to be 
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
    /** @brief This method helps display the ShoppingCart in human readable form
    *   @return void
    */
    void display() const;
    /** @brief A helper method to update a purchase order in the cart
    *   @return void
    */
    void updateOrder();
    /** @brief returns a pointer to the purchase order
    *   @param[in] Id The id of the intended purchase order
    *   @return const PurchaseOrder*
    */
    const PurchaseOrder* getPurchaseOrderById(uint16_t Id) const;
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

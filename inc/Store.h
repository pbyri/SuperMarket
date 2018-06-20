/** @file Store.h
*   @brief This file provides the prototype and public interfaces for the
*   Store class
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*/

#ifndef SUPERMARKET_STORE_H
#define SUPERMARKET_STORE_H
#include <string>
#include <memory>
#include "Helpers.h"

/** @brief namespace SuperStore encapsulates all definitions for SuperMarket
*/
namespace SuperStore
{
  /*!< Forward declarations */
  class Inventory;
  class Product;
  class PurchaseOrder;
  class ShoppingCart;
  /** @brief class Store: prototypes the grocery store
  *
  * This class represents a super market store
  *
  */
  class Store
  {
  public:
  /** @brief enum for Main Menu Selection
  */
  enum class MainMenuChoice
  {
    EXIT_MAIN_MENU = 0,  /*!< choose this option to exit the application */
    CUSTOMER,            /*!< choose this option if you are a customer */
    STORE_ADMIN          /*!< choose this option if you are store admin */
  };
  /** @brief enum for Store Admin Menu Selection
  */
  enum class StoreAdminChoice
  {
    RETURN_TO_MAIN_MENU = 0, /*!< option for returning to main menu */
    ADD_NEW_PRODUCT,         /*!< option for adding new product to inventory */
    DELETE_PRODUCT,          /*!< option to delete existing product from inventory */
    VIEW_INVENTORY           /*!< option to view the inventory */
  };
  /** @brief enum for customer menu selection
  */
  enum class CustomerMenuChoice
  {
    RETURN_TO_MAIN_MENU,   /*!< opotion to return to main menu */
    PURCHASE_PRODUCT,      /*!< option to purchase a product */
    EDIT_SHOPPING_CART,    /*!< option to make changes to shopping cart */
    CHECKOUT_AND_PAY       /*!< option to checkout and pay dues to the store */
  };
  /** @brief enum for choice while editing shopping cart
  */
  enum class EditCartChoice
  {
    DONE,         /*!< Done and go back to previous screen */
    DELETE_ORDER, /*!< Delete an order from the cart */
    UPDATE_ORDER  /*!< Update an order in the cart */
  };
  /** @brief Constructor with std::string parameter
  *   @param[in] name A string that contains the name of the Store
  */
  Store(const std::string &name
       , InStreamHolder &stream = cin_holder());
  /** @brief returns the name of the Store
  *   @return std::string
  */
  std::string getName() const;
  /** @brief returns the number of prodiucts in the Store
  *   @return uint16_t
  */
  uint16_t getInventorySize() const;
  /** @brief A helper function to add a new product to the Store Inventory
  *   @param[in] product A unique_ptr of Product type that needs to be added
  *   to the store inventory
  *   @return bool
  *
  *   This method takes a product object as an input oarameter and
  *   adds that to the store's inventory. If successful, returns true. Otherwise
  *   it returns false.
  *
  */
  bool addProductToInventory(std::unique_ptr<Product> product);
  /** @brief A helper function to remove a product from Store Inventory
  *   @param[in] Id A unique id that identifies a product to be removed from
  *   the store inventory
  *   @return bool
  *
  *   This method takes a 16 bit identifier as input and tries to
  *   remove that product from the store's inventory. if product 
  *   cannot be found. it returns false. If successfully removed, it returns
  *   true
  *
  */
  bool removeProductFromInventory(uint16_t id);
  /** @brief Displays the Main Menu or home page menu
  *   @return void
  *
  *   This method displays the main menu where the user can choose a sub-menu that
  *   they are interested in
  *
  */
  void displayMainMenu() const;
  /** @brief Displays the menu for store administrator
  *   @return void
  *
  *   This method displays a menu for the store manager and facilitates making
  *   changes to the inventory
  *
  */
  void displayStoreAdminMenu() const;
  /** @brief Displays the Menu for customer
  *   @return void
  *
  *   This method displays the menu appropriate for a customer shopping at the
  *   store
  *
  */
  void displayCustomerMenu() const;
  /** @brief This method will handle core interaction functionality of the
  *   Store
  *   @return void
  *
  *   This method will launch the store application and takes to home screen and
  *   takes appropriate action based on user choice
  *
  */
  void launch();
  /** @brief Displays the inventory of the store
  *   @return void
  *
  *   This method displays the entire inventory contained in the store
  *
  */
  void displayInventory() const;
  /** @brief provide functionalities useful to customer of the store
  *   @return void
  *
  *   This method handles customer interaction functions
  *
  */
  void serviceCustomer();
  /** @brief provide functionalities useful to admin of the store
  *   @return void
  *
  *   This method handles store admin interaction function
  *
  */
  void serviceStoreAdmin();
  /**Destructor
  */
  ~Store();
  private:
  /** @brief This is the catalog that lists the whole inventory of products 
  *   available in this market
  */
  std::unique_ptr<Inventory> m_pInventory;
  std::string m_name; /*!< Name of the store */
  static uint16_t order_id; /*!< a hack to maintain unique order_id */
  std::unique_ptr<ShoppingCart> m_cart; /*!< Shopping Cart */
  InStreamHolder m_iStream; /*!< Holder for input stream */

  /** @brief This is a helper method to create a new product and add it to inventory
  *   @return void
  */
  void addNewProduct();

  /** @brief This is a UI interactive method that helps delete a product
  *   @return void
  */
  void deleteProduct();
  /** @brief gets input from a stream for creating a purchase order
  *   @param[in] s An input stream from which to read the data
  *   @return std::unique_ptr<PurchaseOrder>
  *
  *   This method gets input from the user and creates a PurchaseOrder based on
  *   the inputs provided. If the PurchaseOrder could not be created, it returns
  *   an empty unique_ptr
  */
  std::unique_ptr<PurchaseOrder> getPurchaseOrderFromStream(std::istream &s);
  /** @brief This function provides all the functionality required to purchase
   *  a product for the customer
   *  @return void
   */
   void purchaseProduct();
  /** @brief This method displays the Shopping Cart and also helps make changes
  *   to the shopping cart
  */
  void deleteOrder();
  void updateOrder();
  void viewOrEditShoppingCart();
  };
}
#endif

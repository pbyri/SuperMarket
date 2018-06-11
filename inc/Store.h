#ifndef SUPERMARKET_STORE_H
#define SUPERMARKET_STORE_H
#include <string>
#include <memory>

namespace SuperStore
{
  /*!< pre declarations */
  class Inventory;
  class Product;
  /** Store class
  * This class represents a super market store
  *
  */
  class Store
  {
  public:
  /** Constructor
  */
  Store(const std::string &name);
  /** getName method
  *   This method returns the name of the store
  */
  std::string getName() const;
  /** getInventorySize() method
  *   Returns the size of inventory held by the store
  */
  uint16_t getInventorySize() const;
  /** addProductToInventory method
  *   This method takes a product object as an input oarameter and
  *   adds that to the store's inventory
  */
  bool addProductToInventory(std::shared_ptr<Product> product);
  /** removeProductFromInventory
  *   This method takes a 16 bit identifier as input and tries to
  *   remove that product from the store's inventory. if product 
  *   cannot be found. it returns false
  */
  bool removeProductFromInventory(uint16_t id);
  /** displayMainMenu method
  *   This method displays the main menu where the user can choose a sub-menu that
  *   they are interested in
  */
  void displayMainMenu() const;
  /** displayStoreAdminMenu method
  *   This method displays a menu for the store manager and facilitates making
  *   changes to the inventory
  */
  void displayStoreAdminMenu() const;
  /** displayCustomerMenu method
  *   This method displays the menu appropriate for a customer shopping at the
  *   store
  */
  void displayCustomerMenu() const;
  /** launch method
  *   This method will launch the store application and takes to home screen
  */
  void launch();
  /** displayInventory method
  *   This method displays the entire inventory contained in the store
  */
  void displayInventory() const;
  /** serviceCustomer method
  *   This method handles customer interaction functions
  */
  void serviceCustomer();
  /** serviceStoreAdmin method
  *   This method handles store admin interaction function
  */
  void serviceStoreAdmin();
  /**Destructor
  */
  ~Store();
  private:
  /** This is the catalog that lists the whole inventory of products available
  *   in this market
  */
  std::unique_ptr<Inventory> m_pInventory;
  std::string m_name; /*!< Name of the store */
  };
}
#endif

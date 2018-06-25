/** @file Inventory.h
*   @brief Prototypes and Interfaces for Inventory class
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*
*   This file Prototypes the Inventory class under the SuperStore namespace.
*
*/
#ifndef SUPERMARKET_CATALOG_H
#define SUPERMARKET_CATALOG_H
/* include directories */
#include <unordered_map>
#include <memory>
#include <string>

/** @brief namespace SuperStore encapsulates all definitions for SuperMarket
*/
namespace SuperStore
{
  /* pre declarations */
  class Product;
  /** @brief class Inventory: prototypes a collection of Products
   *
   *  This class contains the whole inventory of products being sold at
   *  the supermarket and also provides interfaces to modify the inventory
   *  and query the inventory.
   *
   */
  class Inventory
  {
    public:
      /*!< typedef for Catalog */
      typedef std::unordered_map<uint16_t, std::shared_ptr<Product>> Catalog;
      /** @brief Constructor with std::string argument
       *  @param[in] name: Name of the supermarket
       */
      Inventory(const std::string &name);
      /** @brief returns the name of the Inventory
       *  @return std::string
       */
      inline std::string getName() const;
      /** @brief A helper function to add new Product to the Inventory
       *  @param[in] product A unique_ptr of Product type
       *  @return bool
       *  This method takes a product object and adds it to the inventory of
       *  the supermarket. If the product was successfully added to the inventory
       *  the function returns true. Otherwise it returns false.
       *
       */
      bool addProduct (std::unique_ptr<Product> product);
      /** @brief A helper function to remove an existing Product from Inventory
       *  @param[in] product_id unique identifier of the Product that needs to
       *  be removed from the Inventory
       *  @return void
       *
       */
      void removeProduct(uint16_t product_id);
      /** @brief Displays the entire Inventory on the screen
       *  @return void
       *
       *  This method displays the inventory of the supermarket in a human
       *  readable format
       */
      void displayCatalog()  const;
      /** @brief check if there is a product with specific id in the Inventory
      *   @param[in] id A unique id representing a Product
      *   @return bool
      *
      *   This method takes a 16 bit id as a parameter and returns true if
      *   there exists a product with that id in the inventory. Otherwise, it
      *   returns false
      */
      bool hasProductById(uint16_t id) const;
      /** @brief get a handle to a Product represented by a specific Id
      *   @param[in] id A unique Id presenting a Product in the inventory
      *   @return std::shared_ptr<Product>
      *
      *   This method takes a 16 bit id as input and returns a pointer to
      *   the Product represented by this id
      *   This method needs to be called as follows :
      *   @code
      *   //only call getProductById if the product exists in the Inventory
      *   if(inventory.hasProductById(Id))
      *   {
      *      auto product = inventory.getProductById();
      *   }
      *   // Or guard against nullptr check
      *   auto product = inventory.getProductById();
      *   if(product)
      *   {
      *      //rest of the code goes here
      *   }
      *   @endcode
      */
      std::shared_ptr<Product> getProductById(uint16_t id);
      /** @brief get number of distinct Product types present in the Inventory
      *   @return uint16_t
      *
      *   Returns the number of distinct products available in the inventory
      */
      uint16_t getProductCount() const;
      /** Destructor
       */
      ~Inventory();
    private:
      Catalog m_catalog; /*!< Catalog of all products held in this Inventory */
      std::string m_name; /*!< Name of the Inventory */
  }; // class Inventory
/***********************************************************************************************/
/* Definition of Inline functions */

  std::string Inventory::getName() const
  {
    return m_name;
  }
} // namespace SuperStore
#endif

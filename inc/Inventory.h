#ifndef SUPERMARKET_CATALOG_H
#define SUPERMARKET_CATALOG_H
/* include directories */
#include <unordered_map>
#include <memory>
#include <string>

namespace SuperStore
{
  /* pre declarations */
  class Product;
  /** Inventory class
   *  This class contains the whole inventory of products being sold at 
   *  the supermarket.
   */
  class Inventory
  {
    public:
      /*!< typedef for Catalog */
      typedef std::unordered_map<uint16_t, std::shared_ptr<Product>> Catalog;
      /** Constructor
       * @param name: Name of the supermarket
       */
      Inventory(const std::string &name);
      /** getName method
       */
      inline std::string getName() const;
      /** addProduct  method
       * This method takes a product object and adds it to the inventory of 
       * the supermarket
       */
      bool addProduct (std::shared_ptr<Product> product);
      /** removeProduct method
       * This method takes a unique 16 bit ID for a product, looks for that
       * product in the inventory and removes it
       */
      void removeProduct(uint16_t product_id);
      /** DisplayCatalog method
       * This method displays the inventory of the supermarket in a human 
       * readable format
       */
      void displayCatalog()  const;
      /** hasProductById method
      *   This method takes a 16 bit id as a parameter and returns true if 
      *   there exists a product with that id in the inventory
      */
      bool hasProductById(uint16_t id) const;
      /** getProductById method
      *   This method takes a 16 bit id as input and returns a pointer to
      *   the Product represented by this id
      */
      const Product* getProductById(uint16_t id);
      /** getProductCount() method
      * Returns the number of distinct products available in the inventory
      */
      uint16_t getProductCount() const;
      /** Destructor
       */
      ~Inventory();
    private:
      Catalog m_catalog; /*!< Catalog of all products held at this 
                              SuperMarket */
      std::string m_name; /*!< Name of the SuperMarket */
  };
/***********************************************************************************************/
/** Definition of Inline functions
*
*/

  std::string Inventory::getName() const
  {
    return m_name;
  }
}
#endif
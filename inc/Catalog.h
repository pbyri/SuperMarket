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
  /** Catalog class
   *  This class contains the whole inventory of products being sold at 
   *  the supermarket.
   */
  class Catalog
  {
    public:
      /*!< typedef for inventory */
      typedef std::unordered_map<uint16_t, std::unique_ptr<Product>> Inventory;
      /** Constructor
       * @param name: Name of the supermarket
       */
      Catalog(const std::string &name);
      /** getName method
       */
      inline std::string getName() const;
      /** AddProdiuctToInventory method
       * This method takes a product object and adds it to the inventory of 
       * the supermarket
       */
      bool addProductToInventory(std::unique_ptr<Product> product);
      /** RemoveProductFromInventory method
       * This method takes a unique 16 bit ID for a product, looks for that
       * product in the inventory and if found, removes it
       */
      bool removeProductFromInventory(uint16_t product_id);
      /** Destructor
       */
      /** DisplayInventory method
       * This method displays the inventory of the supermarket in a human readable
       * format
       */
      void displayInventory()  const;
      ~Catalog();
    private:
      Inventory m_inventory; /*!< Inventory of all products held at this SuperMarket */
      std::string m_name; /*!< Name of the SuperMarket */
  };
/***********************************************************************************************/
/** Definition of Inline functions
*
*/

  std::string Catalog::getName() const
  {
    return m_name;
  }
}
#endif

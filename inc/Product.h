/** @file Product.h
*   @brief This file provides prototype and public interfaces for Product class
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*
*/

#ifndef SUPERMARKET_PRODUCT_H
#define SUPERMARKET_PRODUCT_H
#include <string>
#include <cstdint>
#include <memory>

/** @brief namespace SuperStore encapsulates all definitions for SuperMarket
*/
namespace SuperStore
{
  /** @brief class Product: prototype for a product sold at the store
  *
  * This class represents a product sold in the store
  */

  class Product
  {
  public:
    /** @brief This is an interactive static factory method that helps create 
    *   a new Product
    *   @return shared_ptr<Product>
    */
    static std::shared_ptr<Product> CreateNewProduct();
    /** @brief Constructor with parameters
    *   @param[in] Id A unique Id representing this Product
    *   @param[in] description A string that provides a brief description of
    *   the product
    *   @param[in] price The price of the product
    */
    Product(uint16_t id, const std::string &description, double price);
    /** @brief get the unique Id that presents this Product
    *   @return unit16_t
    *
    *   This method returns a unique 16 bit identifier that represents this
    *   product.
    *
    */
    inline uint16_t getID() const;
    /** @brief get a description of the product
    *   @return std::string
    *
    * This method returns a brief description or title for the prouct
    *
    */
    inline std::string getDescription() const;
    /** @brief get the price of the product
    *   @return double
    *
    * This methid returns the price for which a product is available for purchase
    *
    */
    inline double getPrice() const;
    /** Destructor
    */
    ~Product();
  private:
    uint16_t m_id; /*!< unique 16 bit identifier for the product */
    std::string m_description; /*!< A brief title for  product */
    double m_price; /*!< A price for which the product is available
			 for purchase */

    /** @brief A helper function to safely read product Id from console 
    *   @return uint16_t
    */
    static uint16_t getProductIdFromConsole();
  
    /** @brief A helper function to help read product description from console
    *   @return std::string
    */
    static std::string getProductDescriptionFromConsole();

    /** @brief A helper function to help read product price from console
    *   @return double
    */
    static double getProductPriceFromConsole();

  };

/************************************************************************************************/
  /** Definition of Inline functions
  *
  */
  uint16_t Product::getID() const
  {
    return m_id;
  }

  std::string Product::getDescription() const
  {
    return m_description;
  }

  double Product::getPrice() const
  {
    return m_price;
  }
}
#endif

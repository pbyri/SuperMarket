#ifndef SUPERMARKET_PRODUCT_H
#define SUPERMARKET_PRODUCT_H
#include <string>
#include <cstdint>

namespace SuperStore
{
  /** Product class
  * This class represents a product sold in the store
  */

  class Product
  {
  public:
    /** Constructor
    *
    */
    Product(uint16_t id, const std::string &description, double price);
    /** getID method
    * This method returns a unique 16 bit identifier that represents this product
    */
    inline uint16_t getID() const;
    /** getDescription method
    * This method returns a brief descriptior or title for the prouct
    */
    inline std::string getDescription() const;
    /** getPrice method
    * This methid returns the price for which a product is available for purchase
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

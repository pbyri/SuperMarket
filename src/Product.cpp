/** @file Product.cpp
*   @brief This file contains implementation details of the Product class
*   @author Pavan Kumar Byri
*   @date 06-13-2018
*
*   This file provides implementation to Product class 
*
*/

#include "Product.h"

using namespace SuperStore;

Product::Product(uint16_t id, const std::string &description, double price)
    :m_id(id),
    m_description(description),
    m_price(price)
{
}

Product::~Product()
{
}


/** @file Product.cpp
*   @brief This file contains implementation details of the Product class
*   @author Pavan Kumar Byri
*   @date 06-13-2018
*
*   This file provides implementation to Product class 
*
*/

#include "Product.h"
#include <iostream>

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

std::shared_ptr<Product> Product::CreateNewProduct()
{
  uint16_t Id = 0;
  std::string name;
  double price = 0;
  std::cout<<"Please enter a unique Id for the product:";
  std::cin >> Id;
  std::cout<<"Please enter a brief description for the product";
  std::cin >> name;
  std::cout << "Please enter the price of the product:";
  std::cin >> price;
  return std::make_shared<Product>(Id,
                                   name,
                                   price); 
}

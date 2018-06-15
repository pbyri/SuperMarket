/** @file Product.cpp
*   @brief This file contains implementation details of the Product class
*   @author Pavan Kumar Byri
*   @date 06-13-2018
*
*   This file provides implementation to Product class 
*
*/

#include "Helpers.h"
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

uint16_t Product::readProductIdFromConsole()
{
  std::cout<<"Please enter a unique Id for the product:";
  int value = 0;
  // Stay in this function until we can successfully read data from console
  while(true)
  {
    // try to product id input from console
    //GetDataFromStream<int> g(value);
    //std::cin >> g;
    if(std::cin >> GetDataFromStream<int>(value))
    {
      std::cout << "Please enter a valid uint16 number\n";
    }
    // check whether the user entered a valid data
    if(value < 0 || value > UINT16_MAX)
    {
      std::cout << "Please enter a valid uint16 number\n";
    }
    else
    {
      break;
    }
  } // while(true)
  return value;
}// readProductIdFromConsole

std::shared_ptr<Product> Product::CreateNewProduct()
{
  std::string name;
  double price = 0;
  //auto Id = readProductIdFromConsole();
  uint16_t Id = 0;
  std::cout<<"Please enter a brief description for the product:";
  std::cin >> name;
  std::cout << "Please enter the price of the product:";
  std::cin >> price;
  return std::make_shared<Product>(Id,
                                   name,
                                   price); 
}

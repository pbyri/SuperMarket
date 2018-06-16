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

uint16_t Product::getProductIdFromConsole()
{
  std::cout<<"Please enter a unique Id for the product:";
  int value = 0;
  do
  {
    std::cin >> GetDataFromStream<int>(value);
    // check whether the user entered a valid data
    if(value < 0 || value > UINT16_MAX)
    {
      std::cout << "Please enter a valid uint16 number : ";
    }
    else
    {
      break;
    }
  }while(true);
  return value;
}// readProductIdFromConsole

std::string Product::getProductDescriptionFromConsole()
{
  std::cout<<"Please enter a brief description for the product:";
  std::string desc;
  do
  {
    std::getline(std::cin, desc);
    if(desc.length())
    {
      break;
    }
  }while(true);
  return desc;
}

double Product::getProductPriceFromConsole()
{
  std::cout << "Please enter the price of the product:";
  double price = 0;
  do
  {
    std::cin >> GetDataFromStream<double>(price);
    if(price <= 0)
    {
      std::cout << "Please enter a value greater than zero for price : ";
      continue;
    }
    else
    {
      break;
    }
  }while(true);
  return price;
}
std::shared_ptr<Product> Product::CreateNewProduct()
{
  auto Id = Product::getProductIdFromConsole();
  auto name = Product::getProductDescriptionFromConsole();
  auto price = Product::getProductPriceFromConsole();
  return std::make_shared<Product>(Id,
                                   name,
                                   price); 
}

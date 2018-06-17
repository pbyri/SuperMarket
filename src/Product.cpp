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

uint16_t Product::getProductIdFromStream(std::istream &stream)
{
  std::cout<<"Please enter a unique Id for the product:";
  uint16_t product_id;
  do
  {
    product_id =  getUint16FromStream(stream);
  }while(!product_id);// Keep looping until user enters non-zero Id
}// rgetProductIdFromConsole

/** @TODO DO NOT ALLOW WHITESPACES TO BE A VALID DESCRIPTION */
std::string Product::getProductDescriptionFromStream(std::istream &stream)
{
  std::cout<<"Please enter a brief description for the product:";
  std::string desc;
  do
  {
    std::getline(stream, desc);
  }while(!desc.length());// Keep looping until user enters a non-empty description
  return desc;
}

double Product::getProductPriceFromStream(std::istream &stream)
{
  std::cout << "Please enter the price of the product:";
  double price = 0;
  do
  {
    price = getDoubleFromStream(stream);
  }while(price <= 0); // keep looping until user enters a positive number
  return price;
}
std::unique_ptr<Product> Product::CreateNewProductFromStream(std::istream &inStream)
{
  auto Id = Product::getProductIdFromStream(inStream);
  auto name = Product::getProductDescriptionFromStream(inStream);
  auto price = Product::getProductPriceFromStream(inStream);
  return std::make_unique<Product>(Id,
                                   name,
                                   price); 
}

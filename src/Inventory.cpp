/** @file Inventory.cpp
*   @brief Implementation details of the Inventory
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*
*   This file contains the implementation details of Inventory class 
*
*/
#include "Inventory.h"
#include <iostream>
#include "Product.h"
#include "assert.h"

using namespace SuperStore;

Inventory::Inventory(const std::string &name) : m_name(name)
{
}

bool Inventory::addProduct(std::shared_ptr<Product> product)
{
  // if the inventory already has a product with the given Id, return false
  // Otherwise, add the product to the catalog and return true
  if(hasProductById(product->getID()))
  {
    return false;
  }
  m_catalog[product->getID()] = product;
  return true;
}

// If the inventory has a product with the give id, remove it from the catalog
// and return
void Inventory::removeProduct(uint16_t product_id)
{
  if(hasProductById(product_id))
  {
    m_catalog.erase(product_id);
  }
}

void Inventory::displayCatalog() const
{
  if(!getProductCount())
  {
    std::cout<<"Sorry, the inventory is empty. Please contact store manager\n";
    return;
  }
  std::cout<<"================================================================\n";
  std::cout<<"ProductID     Description                         Price\n";
  std::cout<<"================================================================\n";

  // Iterate through the Catalog Map and print the details of each Product
  for(auto const &KeyVal : m_catalog)
  {
    std::cout<< KeyVal.first <<"      ";
    std::cout<< KeyVal.second->getDescription() <<"     ";
    std::cout<< KeyVal.second->getPrice() << "\n";
  }
}

// check the catalog for a product with given Id. if found, return true.
// Otherwise return false.
bool Inventory::hasProductById(uint16_t id) const
{
  if(m_catalog.find(id) != m_catalog.end())
  {
    return true;
  }
  return false;
}

// if the inventory has a product with the given Id, return a pointer to the
// Product object. Otherwise, return nullptr
const Product* Inventory::getProductById(uint16_t id) 
{
 assert(this->hasProductById(id));

 if(this->hasProductById(id))
 {
   return m_catalog[id].get();
 }
 return nullptr;
}

// return the size of the catalog as the size of the Inventory
uint16_t Inventory::getProductCount() const
{
  return m_catalog.size();
}

Inventory::~Inventory()
{
}


#include <iostream>
#include <Inventory.h>
#include <memory>

#ifdef TEST_SUPER_MARKET
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#endif

using namespace SuperStore;
#ifndef TEST_SUPER_MARKET
int main()
{
  auto catalog = std::make_unique<Inventory>("Joes");
  std::cout<<"Welcome to " << catalog->getName() << " super market\n";
  catalog->displayCatalog();
  return 0;  
}

#endif



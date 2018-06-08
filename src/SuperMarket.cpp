#include <iostream>
#include <Catalog.h>
#include <memory>

#ifdef TEST_SUPER_MARKET
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#endif

using namespace SuperStore;
#ifndef TEST_SUPER_MARKET
int main()
{
  auto catalog = std::make_unique<Catalog>("Joes");
  std::cout<<"Welcome to " << catalog->getName() << " super market\n";
  catalog->displayInventory();
  return 0;  
}

#endif



#include <iostream>
#include <Store.h>
#include <memory>

#ifdef TEST_SUPER_MARKET
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#endif

using namespace SuperStore;
#ifndef TEST_SUPER_MARKET
int main()
{
  auto store = std::make_unique<Store>("Joe\'s");
  store->displayMainMenu();
  return 0;  
}

#endif



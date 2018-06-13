/** @file SuperMarket.cpp
*   @brief This is the entry point file for this project
*   @author Pavan Kumar Byri
*   @date 06-12-2018
*/

#include <iostream>
#include <Store.h>
#include <memory>

#ifdef TEST_SUPER_MARKET
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#endif

using namespace SuperStore;
#ifndef TEST_SUPER_MARKET
// Just create an instance of Store and invoke launch() method on it.
// Let it handle the rest. When the control returns back, print an exiting
// message and exit.
int main()
{
  auto store = std::make_unique<Store>("Joe\'s");
  store->launch();
  std::cout<<"Exiting application..";
  return 0;  
}

#endif



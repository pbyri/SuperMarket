/** @file HelpersTest.pp
*   @brief This file contains unit tests for Helpers.cpp
*   @author Pavan Kumar Byri
*   @date 06-17-2018
*/


#include "Helpers.h"
#include "catch.hpp"
#include <limits>

using namespace SuperStore;

TEST_CASE("Test getIntFromStream","[Helpers]")
{
  std::istringstream iss;
  iss.str("123\n");
  REQUIRE(123 == getIntFromStream(iss));
  iss.str("-123\n");
  REQUIRE(-123 == getIntFromStream(iss));
  iss.str("hello\n123\n");  
  REQUIRE(123 == getIntFromStream(iss));
  iss.str("123 hello\n456\n");  
  REQUIRE(456 == getIntFromStream(iss));
  iss.str("123.45\n67\n");  
  REQUIRE(67 == getIntFromStream(iss));
  iss.str("   123\n");
  REQUIRE(123 == getIntFromStream(iss));
  iss.str("897   \n");
  REQUIRE(897 == getIntFromStream(iss));
  iss.str("123.\n43\n");
  REQUIRE(43 == getIntFromStream(iss));
  iss.str("123\n43\n");
  REQUIRE(123 == getIntFromStream(iss));
  iss.str("123.\n-43\n");
  REQUIRE(-43 == getIntFromStream(iss));
}

TEST_CASE("Test getUnit16FromConsole","[Helpers]")
{
  std::istringstream iss;
  iss.str("-1\n1\n");
  REQUIRE(1 == getUint16FromStream(iss));
  iss.str("0\n");
  REQUIRE(0 == getUint16FromStream(iss));
  std::string s(std::to_string(UINT16_MAX) + "\n");
  iss.str(s);
  REQUIRE(UINT16_MAX == getUint16FromStream(iss));
  s = std::to_string((UINT16_MAX + 1)) + "\n12\n";
  iss.str(s);
  REQUIRE(12 == getUint16FromStream(iss));
}

TEST_CASE("Test getDoubleFromConsole","[Helpers]")
{
  std::istringstream iss;
  iss.str("12.22\n");
  REQUIRE(12.22 == getDoubleFromStream(iss));
  iss.str("-11.11\n");
  REQUIRE(-11.11 == getDoubleFromStream(iss));
  iss.str("hello\n12\n");
  REQUIRE(12 == getDoubleFromStream(iss));
}

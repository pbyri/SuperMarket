/** @file Helpers.cpp
*   @brief This file contains helper utility functions
*   @author Pavan Kumar Byri
*   @date 06-16-2018
*/

#include "Helpers.h"

namespace SuperStore
{
  /** @brief this method safely reads an integer from a stream and returns the value
  *   @returns int
  */

  int getIntFromStream(std::istream &stream)
  {
    int data;
    while(!(stream >> GetDataFromStream<int>(data)))
    {
      //loop until stream is in invalid state. exit when stream is good 
    }
    return data;
  }

  /** @brief This is a helper method to safely read uint16_t from a stream
  *   @return uint16_t
  */
  uint16_t getUint16FromStream(std::istream &stream)
  {
    int data;
    do
    {
      data = getIntFromStream(stream);
    }while(data < 0 || data > UINT16_MAX);
    return data;
  }
  /** @brief this method safely reads a double from a stream and returns it
  *   @returns double
  */

  double getDoubleFromStream(std::istream &stream)
  {
    double data;
    while(!(stream >> GetDataFromStream<double>(data)))
    {
      //loop until stream is in invalid state. exit when stream is good 
    }
    return data;
  }


}// namespace SuperStore

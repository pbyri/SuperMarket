/** @file StreamWrapper.cpp
*   @brief This file provides implementation of the InStreamWrapper class
*   @author Pavan Kumar Byri
*   @date 06-21-2018
*/

#include "StreamWrapper.h"

using namespace SuperStore;

InStreamHolder& cin_holder()
{
  static InStreamHolder in(std::cin);
  return in;
}

InStreamHolder::InStreamHolder(std::istream &stream)
    : m_inStream(stream)
{
}


InStreamHolder::operator std::istream&()
{
  return m_inStream;
}


InStreamWrapper::InStreamWrapper(InStreamHolder& holder)
    : m_holder(holder)
{
}

std::istream& InStreamWrapper::getInputStream()
{
  return m_holder;
}


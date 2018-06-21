/** @file StreamWrapper.h
*   @brief This file provides prorotyes for an Input Stream Wrapper class
*   @author Pavan Kumar Byri
*   @date 06-21-2018
*/

#ifndef SUPERMARKET_STREAMWRAPPER_H
#define SUPERMARKET_STREAMWRAPPER_H

#include <iostream>

namespace SuperStore
{
  /** @brief a class for istream holder
  */
  class InStreamHolder
  {
   public:
   /** @brief Constructor that takes a reference to an input stream
   *   @param[in] stream A reference to an input stream\
   */
   InStreamHolder(std::istream &stream = std::cin);
   InStreamHolder(const InStreamHolder&) = delete;
   const InStreamHolder& operator =(const InStreamHolder &) = delete;
   /** @brief operator to return the contained istream object reference
   *   @return std::istream&
   */
   operator std::istream&();
   private:
   std::istream &m_inStream; /*!< reference of the input stream being wrapped */
  }; 

  InStreamHolder& cin_holder();

  /** @brief A class for wrapping an input stream using the InStreamHolder object
      and provides an interface to get the underlying inputstream
  */
  class InStreamWrapper
  {
  public:
    InStreamWrapper(InStreamHolder &h = cin_holder());
    InStreamWrapper(const InStreamWrapper&) = delete;
    const InStreamWrapper& operator =(const InStreamWrapper&) = delete;
  protected:
    std::istream& getInputStream();
  private:
    InStreamHolder &m_holder;
  };
}
#endif

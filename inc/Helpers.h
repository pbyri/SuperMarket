/** @file Helpers.h
*   @brief This file contains prototypes of helper utility functions
*   @author Pavan Kumar Byri
*   @date 06-14-2018
*/
#ifndef SUPERMARKET_HELPERS_H
#define SUPERMARKET_HELPERS_H
#include <iostream>
#include <string>
#include <sstream>

namespace SuperStore
{
  /** @brief A templatized helper class for safely reading a non-string data
  *   type from a given input stream
  */
  template<typename DataType>
  class GetDataFromStream
  {
    public:
    /** @brief Constructor that takes one parameter
    *   @param[in] value The variable where the value from the input stream
    *   needs to be stored into
    */
    GetDataFromStream<DataType>(DataType &value);
    /** @brief operator to read data from stream
    *   @param[in] stream Input stream from which to read data
    *   @obj[in]   An object of GetDataFromStream<T> that denotes the type of
        data to be read from the stream
    *   @return std::istream&
    */
    friend std::istream& operator >>(std::istream &stream, 
                                    GetDataFromStream<DataType> &&obj)
    {
      obj.val_ = obj.readDataFromStream(stream);
      return stream;
    }
    private:
    /*!< referece to the variable where the data from the stream needs to be
    read into */
    DataType &val_; 
    /** @brief A helper function to safely read the expected data from a given
    *   input stream
    *   @param[in] stream Input stream from which to read the data
    *   @return DataType
    */
    DataType readDataFromStream(std::istream &stream);
  };


/*****************************************************************************/
/*           FUNCTION DEFINITIONS                                            */
/*****************************************************************************/

  template<typename DataType>
  GetDataFromStream<DataType>::GetDataFromStream(DataType &v) : val_(v)
  {
  }

  template<typename DataType>
  DataType GetDataFromStream<DataType>::readDataFromStream(std::istream &stream)
  {
    DataType data;   /*!< stores the actual value read from stream */
    std::string user_input; /*!< a string to read user input from the stream */
    // Continue to loop as long as the stream is valid and user inputs a line 
    // into the stream
    // read a line from the stream into 'user_input'
    while(stream 
         && (std::getline(stream, user_input)))
    {
      // pass the line into a stringstream object
      std::istringstream instream{user_input};
      // The data entered can be properly read into the destination DataType
      // and there is no trailing non-whitespace characters after that
      if((instream >> data) && !(instream >> user_input))
      {
        // we have successfully read the desired data from the stream. Exit now
        break;
      }
    } // while
    return data;
  } // GetDataFromStream::readDataFromstream()
  /** @brief this method safely reads an integer from a stream and returns the value
  *   @returns int
  */

  int getIntFromStream(std::istream &stream);
  /** @brief This is a helper method to safely read uint16_t from a stream
  *   @return uint16_t
  */
  uint16_t getUint16FromStream(std::istream &stream);
  /** @brief this method safely reads a double from a stream and returns it
  *   @returns double
  */

  double getDoubleFromStream(std::istream &stream);

} // namespace SuperStore
#endif

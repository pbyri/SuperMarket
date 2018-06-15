/** @file Helpers.h
*   @brief This file contains prototypes of helper utility functions
*   @author Pavan Kumar Byri
*   @date 06-14-2018
*/
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
                                    GetDataFromStream<DataType> &obj)
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
    // Only loop as long as the stream is valid. Otherwise it leads to an
    // infinite loop
    while(stream)
    {
      std::string input_data; /*!< captures the input data from the input stream */
      // read a line from the input stream
      std::getline(stream, input_data);
      // push the user input data into a string stream
      std::stringstream input_stream(input_data);
      /*!< variable to store the desired data safely extracted from the stream */
      DataType value;

      if(!(input_stream >> value))
      {
        // The data from the stream was not of desired DataType
        std::cout << "Nice try ! Please enter valid data\n";
        continue;
      }
      // Now the data entered has matched expected DataType. But, does it contain
      // trailing undesired data?? Then the input is still invalid
      char trail;

      if(input_stream >> trail)
      {
        std::cout << "Nice try ! Please enter valid data\n";
        continue;
      }
      // we have extracted data safely from the stream. return that
      return value;
    } // while(stream)
    // if we reached here, it means we ran out of input from the input stream
    // and we dont have any valid data yet.Throw exception? revisit this.
    //throw std::invalid_argument("stream is not valid");
    return 0;
  } // GetDataFromStream::readDataFromstream()
} // namespace SuperStore

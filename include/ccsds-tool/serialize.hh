/** Serialization library for ccsds-tool, static part.
 * */
#ifndef _CCSDS_TOOL_SERIALIZE_HH_
#define _CCSDS_TOOL_SERIALIZE_HH_ 1
#include <cstddef>

/** Namespace for ccsds_tool library
 * */
namespace ccsds_tool
{
  /** Serialization function; This function is using (and used by) the
   * code generated using ccsds_tool.
   *
   * The general template function implements a redirection to the
   * objects serialization method. So every class that implements a
   * serialize method can be serialized using this unified interface.
   *
   * Specializations for primitive data types do the actual work of
   * serializing data into the buffer.
   *
   * @param buffer Referenz to a pointer to the buffer. This pointer will be
   * modified when data is written to the buffer. So this is an out parameter.
   * @param x The object to be serialized.
   * */
  template<typename X> void serialize(char *& buffer, X const & x)
  {
    x.serialize(buffer);
  }

  /** Specialization of the serialization function for arrays of known
   * length.
   * */
  template<std::size_t N, typename X>
    void serialize(char *& buffer, X(&array)[N])
    {
      for (std::size_t i = 0; i < N; i++)
      {
        serialize(buffer, array[i]);
      }
    }

  /** Deserialization function; This function is using (and used by) the
   * code generated using ccsds_tool.
   *
   * The general template function implements a redirection to the
   * objects deserialization method. So every class that implements a
   * deserialize method can be deserialized using this unified interface.
   *
   * Specializations for the primitive data types do the actual work of
   * deserializing the data from the buffer.
   *
   * @param buffer Referenz to a pointer to the buffer. This pointer will be
   * modified when data is read from the buffer. So this is an out parameter.
   * @param x The object that gets filled with the data from the buffer.
   * */
  template<typename X> void deserialize(char *& buffer, X & x)
  {
    x.deserialize(buffer);
  }

  /** Specialization of the deserialization function for arrays of known
   * length.
   * */
  template<std::size_t N, typename X>
    void deserialize(char *& buffer, X(&array)[N])
    {
      for (std::size_t i = 0; i < N; i++)
      {
        deserialize(buffer, array[i]);
      }
    }
}

#endif


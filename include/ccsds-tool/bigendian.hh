/** Serialization to big endian.
 *
 * This header contains template specializations for the general
 * serialization function to convert from and to big endian.
 * */
#ifndef _CCSDS_TOOL_BIGENDIAN_HH_
#define _CCSDS_TOOL_BIGENDIAN_HH_ 1

namespace ccsds_tool
{
  template<> void serialize<int>(char *&, int const &);
  template<> void deserialize<int>(char *&, int &);
}
#endif


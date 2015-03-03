#include "ccsds-tool/bigendian.hh"

namespace ccsds_tool
{
  template<> void serialize<int>(char *& buffer, int const & i)
  {
    *buffer++ = i & 0xFF000000;
    *buffer++ = i & 0x00FF0000;
    *buffer++ = i & 0x0000FF00;
    *buffer++ = i & 0x000000FF;
  }
  template<> void deserialize<int>(char *& buffer, int & i)
  {
    i = *buffer++;
    i <<= 8;
    i &= *buffer++;
    i <<= 8;
    i &= *buffer++;
    i <<= 8;
    i &= *buffer++;
  }
}


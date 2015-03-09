#ifndef _DEBUG_COMMA_H_
#define _DEBUG_COMMA_H_ 1
#include <ccsds-tool/serialize.hh>

namespace ccsds_tool
{
  template<> void serialize<int>(char *& buffer, int const & i);
  template<> void deserialize<int>(char *& buffer, int & i);
}

#endif

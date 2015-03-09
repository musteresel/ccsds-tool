#include "debug-comma.hh"
#include <ccsds-tool/serialize.hh>
#include <iostream>

namespace ccsds_tool
{
  template<> void serialize<int>(char *& buffer, int const & i)
  {
    std::cout << "INT: " << i << std::endl;
  }
  template<> void deserialize<int>(char *& buffer, int & i)
  {
  }
}

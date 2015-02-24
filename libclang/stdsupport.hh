/** Support to bridge between C++ std library and clang C types.
 * */
#ifndef _CCSDS_TOOL_STDSUPPORT_HH_
#define _CCSDS_TOOL_STDSUPPORT_HH_ 1
#include "clang-c/Index.h"
#include <functional>

namespace std
{
  template<> struct hash<CXCursor>;
  template<> struct less<CXCursor>;
}

#endif

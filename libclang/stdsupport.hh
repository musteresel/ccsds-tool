/** Support to bridge between C++ std library and clang C types.
 * */
#ifndef _CCSDS_TOOL_STDSUPPORT_HH_
#define _CCSDS_TOOL_STDSUPPORT_HH_ 1
#include "clang-c/Index.h"
#include <functional>

namespace std
{
  template<> struct hash<CXCursor>
  {
    size_t operator()(CXCursor const & cursor) const
    {
      return clang_hashCursor(cursor);
    }
  };
  template<> struct less<CXCursor>
  {
    bool operator()(CXCursor const & lhs, CXCursor const & rhs) const
    {
      auto const h = hash<CXCursor>();
      return h(lhs) < h(rhs);
    }
  };
}

namespace stdSupport
{
  template<typename Container, typename Predicate>
    void erase_if(Container & container, Predicate const & predicate)
    {
      for (auto iterator = std::begin(container);
          iterator != std::end(container);)
      {
        if (predicate(*iterator))
        {
          iterator = container.erase(iterator);
        }
        else
        {
          ++iterator;
        }
      }
    };
}



#endif

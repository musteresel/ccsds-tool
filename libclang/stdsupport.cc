#include "stdsupport.hh"

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


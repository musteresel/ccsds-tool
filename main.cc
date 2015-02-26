#include "libclang/visit.hh"
#include "libclang/filter.hh"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

std::ostream & operator<<(std::ostream & os, CXString str)
{
  os << clang_getCString(str);
  return os;
}

std::ostream & operator<<(std::ostream & os, CXCursor cursor)
{
  CXString spelling = clang_getCursorDisplayName(cursor);
  os << spelling;
  clang_disposeString(spelling);
  return os;
}

void debugDecls(declarations_map_type const & decls)
{
  for (auto decl : decls)
  {
    cout << decl.first << endl;
  }
};


int main(int argc, char ** argv)
{
  auto decls = runClangVisitor(argc - 1, argv + 1);
  debugDecls(decls);
  stdSupport::erase_if(decls, noCodeGenerationRequested);
  cout << "--" << endl;
  debugDecls(decls);
  return 0;
}

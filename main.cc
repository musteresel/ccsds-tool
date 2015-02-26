#include "libclang/visit.hh"
#include "libclang/filter.hh"
#include "output/data.hh"
#include "output/serialization.hh"
#include <iostream>
#include <algorithm>
#include <list>

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


auto const declarationToStructure = [](
    declarations_map_type::value_type const & decl)
{
  CXString spelling = clang_getCursorSpelling(decl.first);
  auto result = Structure(clang_getCString(spelling));
  for (auto const & field : decl.second.fields)
  {
    CXString name = clang_getCursorSpelling(field);
    result.fields.push_front(clang_getCString(name));
    clang_disposeString(name);
  }
  clang_disposeString(spelling);
  return result;
};


int main(int argc, char ** argv)
{
  auto decls = runClangVisitor(argc - 1, argv + 1);
  stdSupport::erase_if(decls, noCodeGenerationRequested);
  debugDecls(decls);
  std::cout << "---" << std::endl;
  // TODO convert one representation to the other
  std::list<Structure> structures;
  for (auto const & decl : decls)
  {
    structures.push_back(declarationToStructure(decl));
  }
  /* TODO for some reason this fails. Investigate why!
   * Seems to be related to the move constructor of the empty forward_list
   * std::transform(decls.begin(), decls.end(), structures.begin(),
      declarationToStructure);*/
  auto outfileArg = std::find(argv + 1, argv + argc,std::string("-o")) + 1;
  if (outfileArg < argv + argc)
  {
    std::cout << "Output to: " << *outfileArg << std::endl;
  }
  for (auto const & structure : structures)
  {
    printSerializationMethod(std::cout, structure);
  }
  return 0;
}


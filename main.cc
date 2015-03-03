#include "libclang/visit.hh"
#include "libclang/filter.hh"
#include "output/data.hh"
#include "output/serialization.hh"
#include <iostream>
#include <fstream>
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
  if (argc < 2)
  {
    // TODO usage
    return 1;
  }
  auto inFile = argv[1];
  char ** firstClang = nullptr;
  auto numClang = 0;
  if (argc > 2)
  {
    firstClang = argv + 2;
    numClang = argc - 2;
  }
  auto declarations = runClangVisitor(inFile, numClang, firstClang);
  stdSupport::erase_if(declarations, noCodeGenerationRequested);
  std::list<Structure> structures;
  for (auto const & declaration : declarations)
  {
    structures.push_back(declarationToStructure(declaration));
  }
  std::cout << "#include <ccsds-tool/serialize.hh>\n"
    << "#include \"" << inFile << "\"\n";
  for (auto const & structure : structures)
  {
    printSerializationMethod(std::cout, structure);
    printDeserializationMethod(std::cout, structure);
  }
  return 0;
}


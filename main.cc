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


struct Arguments
{
  struct
  {
    std::size_t count;
    char const * first;
    char const * input;
  } clang;
  char const * output;
};

  template<typename Container, typename Fn>
void processCmdOption(Container & container, std::string cmd, Fn const & f)
{
  for (auto iterator = std::begin(container), option = iterator++;
      option != std::end(container);)
  {
    if (cmd == *iterator)
    {
      f(*option);
      iterator = container.erase(iterator, option++);
      option = iterator++;
    }
  }
}


Arguments parseArguments(int argc, char const * const * argv)
{
  auto endOfArguments = argv + argc;
  auto separator = std::find(argv, endOfArguments, std::string("--"));
  auto arguments = Arguments();
  arguments.clang.first = (separator == endOfArguments) ?
    separator : (separator + 1);
  arguments.clang.count = endOfArguments - arguments.clang.first;
  auto toolArgs = std::list<char const *>(argv, separator);
  processCmdOption(toolArgs, "-o", [&arguments](char const * file) {
      arguments.output = file;
      });
  // TODO error reporting, not ignoring
  arguments.clang.input = *std::begin(toolArgs);
  return arguments;
}



int main(int argc, char ** argv)
{
  auto arguments = parseArguments(argc - 1, argv + 1);
  auto declarations = runClangVisitor(arguments.clang.input,
      arguments.clang.count, arguments.clang.first);
  stdSupport::erase_if(declarations, noCodeGenerationRequested);
  std::list<Structure> structures;
  for (auto const & declaration : declarations)
  {
    structures.push_back(declarationToStructure(declaration));
  }
  auto outfileArg = std::find(argv + 1, argv + argc,std::string("-o")) + 1;
  std::ofstream outfile;
  std::streambuf *backup;
  if (outfileArg < argv + argc)
  {
    std::cerr << "Output to: " << *outfileArg << std::endl;
    outfile.open(*outfileArg);
    backup = std::cout.rdbuf();
    std::cout.rdbuf(outfile.rdbuf());
  }
  std::cout << "#include <ccsds-tool/serialize.hh>\n"
    << "#include \"--mainfile--\"\n";
  for (auto const & structure : structures)
  {
    printSerializationMethod(std::cout, structure);
  }
  if (outfileArg < argv + argc)
  {
    std::cout.rdbuf(backup);
  }
  return 0;
}


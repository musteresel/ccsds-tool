#include "clang-c/Index.h"
#include <iostream>
#include <set>
#include <map>

char const * nameOf_CXLanguageKind(CXLanguageKind kind)
{
  switch (kind)
  {
    case CXLanguage_CPlusPlus: return "C++";
    case CXLanguage_C: return "C";
    case CXLanguage_ObjC: return "ObjC";
    default: return "Invalid";
  }
}

std::ostream & operator<<(std::ostream & os, CXLanguageKind kind)
{
  os << nameOf_CXLanguageKind(kind);
  return os;
}

std::ostream & operator<<(std::ostream & os, CXString str)
{
  os << clang_getCString(str);
  return os;
}
std::ostream & operator<<(std::ostream & os, CXCursor cursor)
{
  CXString spelling = clang_getCursorSpelling(cursor);
  CXLanguageKind language = clang_getCursorLanguage(cursor);
  CXCursorKind kind = clang_getCursorKind(cursor);
  os << spelling << " (" << language << ")"
    << " kind:" << kind;
  clang_disposeString(spelling);
  return os;
}

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

class Declaration
{
  public:
    using set_type = std::set<CXCursor>;
    set_type fields;
    set_type methods;
};

using declarations_map_type = std::map<CXCursor, Declaration>;

CXChildVisitResult TranslationUnitVisitor(
    CXCursor cursor, CXCursor parent, CXClientData client_data)
{
  if (! clang_Location_isFromMainFile(clang_getCursorLocation(cursor)))
  {
    return CXChildVisit_Continue;
  }
  CXCursorKind kind = clang_getCursorKind(cursor);
  if (! clang_isDeclaration(kind))
  {
    return CXChildVisit_Continue;
  }
  auto declarations = (declarations_map_type *) client_data;
  auto const h = std::hash<CXCursor>();
  std::cout << cursor << " (" << h(cursor) << ") "
    << parent << " (" << h(parent) << ")" << std::endl;
  if (kind == CXCursor_StructDecl || kind == CXCursor_UnionDecl
      || kind == CXCursor_ClassDecl)
  {
    return CXChildVisit_Recurse;
  }
  if (kind == CXCursor_FieldDecl)
  {
    // TODO assert parent == semantic parent
    (*declarations)[parent].fields.insert(cursor);
  }
  else if (kind == CXCursor_CXXMethod)
  {
    (*declarations)[parent].methods.insert(cursor);
  }
  return CXChildVisit_Continue;
}



int main(int argc, char const ** argv)
{
  CXIndex index = clang_createIndex(0, 1);
  CXTranslationUnit translation = clang_parseTranslationUnit(
      index,
      0,
      argv + 1,
      argc - 1,
      0, 0,
      0);
  // TODO Check translation != null
  CXCursor cursor = clang_getTranslationUnitCursor(translation);
  auto declarations = declarations_map_type();
  clang_visitChildren(cursor, TranslationUnitVisitor, &declarations);
  for(auto i : declarations)
  {
    std::cout << i.first;
    auto decl = i.second;
    std::cout << " (" << decl.fields.size() << "|"
      << decl.methods.size() << ") {" << std::endl;
    for (auto f : decl.fields)
    {
      std::cout << "    " << f << std::endl;
    }
    std::cout << "}" << std::endl;
  }
  clang_disposeTranslationUnit(translation);
  clang_disposeIndex(index);
  return 0;
}

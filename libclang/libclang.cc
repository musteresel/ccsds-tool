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
  CXString spelling = clang_getCursorDisplayName(cursor);
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
      || kind == CXCursor_ClassDecl || kind == CXCursor_ClassTemplate
      || kind == CXCursor_ClassTemplatePartialSpecialization)
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

std::ostream & printType(std::ostream & os, CXCursor cursor)
{
  CXType type = clang_getCursorType(cursor);
  CXType canonical = clang_getCanonicalType(type);
  CXString spelling = clang_getTypeSpelling(type);
  CXString canonical_spelling = clang_getTypeSpelling(canonical);
  os << spelling << " - " << canonical_spelling;
  clang_disposeString(spelling);
  clang_disposeString(canonical_spelling);
  return os;
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
  clang_disposeTranslationUnit(translation);
  clang_disposeIndex(index);
  std::cout << "YEAH" << std::endl;
  for(auto i : declarations)
  {
    std::cout << i.first;
    auto decl = i.second;
    std::cout << " :: ";
    printType(std::cout, i.first) << std::endl;
    for (auto f : decl.fields)
    {
      std::cout << "    " << f << " :: ";
      printType(std::cout, f) << std::endl;
    }
    std::cout << "    --" << std::endl;
    for (auto m : decl.methods)
    {
      std::cout << "    " << m << std::endl;
      printType(std::cout, m) << std::endl;
    }
    std::cout << "}" << std::endl;
  }
  return 0;
}
/*
   |-------------------------------------------------v
ARGS --(parse libclang)--> setof Declarations ----> outfile

declCursor -> Declaration
fieldCursor -> field in Declaration
methodCursor -> method in Declaration
*/

class Decl
{
  public:
    virtual void addField(void) = 0;
    virtual void addMethod(void) = 0;
};

/*
 * Decl:
 * NAME (+ namespace)
 * TYPE (Union, Struct, class)
 * BASECLASSES !!!
 * TEMPLATES?!?
 *
 * Field:
 * name
 * TYPE (const, volatile?)
 * static fields?
 *
 * Method:
 * name
 * signature (incl const volatile)
 *
 *
 * Possible ways:
 * 1. Make own interface (like above)
 * 2. Provide access to underlying interface (libclang)
 *
 * 3. BOTH (own interface based on accessors provided by 2
 *
 * Important: 2 must try to be as general as possible, to be safe
 * in case of api (libclang) changes.
 * */


/*
 * libclang: dispose index only after everything has been done. Therefore,
 * consider inversion of control.
 * As an alternative, use reference counting and dispose only after
 * everything has finished using it. Problem: Translation units need
 * a wrapper then, too. So this might become rather complex ... and unneeded.
 * */


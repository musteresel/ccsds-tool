
#include "stdsupport.hh"
#include "clang-c/Index.h"

#include <set>
#include <map>

struct DeclarationContent
{
  using container_type = std::set<CXCursor>;
  container_type fields;
  container_type methods;
};

using declarations_map_type = std::map<CXCursor, DeclarationContent>;



CXChildVisitResult translationUnitVisitor(
    CXCursor cursor, CXCursor parent, CXClientData client_data)
{
  if (! clang_Location_isFromMainFile(clang_getCursorLocation(cursor)))
  {
    return CXChildVisit_Continue;
  }
  CXCursorKind kind = clang_getCursorKind(kind);
  if (! clang_isDeclaration(kind))
  {
    return CXChildVisit_Continue;
  }
  auto declarations = *((declarations_map_type *) client_data);
  if (kind == CXCursor_StructDecl
      || kind == CXCursor_ClassDecl)
  {
    return CXChildVisit_Recurse;
  }
  if (kind == CXCursor_FieldDecl)
  {
    // TODO assert parent == semantic parent
    declarations[parent].fields.insert(cursor);
  }
  else if (kind == CXCursor_CXXMethod)
  {
    declarations[parent].methods.insert(cursor);
  }
  return CXChildVisit_Continue;
}



declarations_map_type runClangVisitor(int argc, char ** argv)
{
  CXIndex index = clang_createIndex(0, 1);
  CXTranslationUnit translation = clang_parseTranslationUnit(
      index,
      0,
      argv,
      argc,
      0, 0,
      0);
  auto declarations = declarations_map_type();
  if (translation)
  {
    clang_visitChildren(cursor, translationUnitVisitor, &declarations);
    clang_disposeTranslationUnit(translation);
  }
  clang_disposeIndex(index);
  return declarations;
}


auto const wrongName = [](std::string name)
{
  return [=name](CXCursor cursor)
  {
    CXString spelling = clang_getCursorSpelling(cursor);
    bool result = (name != clang_getCString(spelling));
    clang_disposeString(spelling);
    return result;
  }
};
auto const wrongSignature = [](std::string signature)
{
  return [=signature](CXCursor cursor)
  {
    CXType type = clang_getCursorType(cursor);
    CXString spelling = clang_getTypeSpelling(type);
    bool result = (signature != clang_getCString(spelling));
    clang_disposeString(spelling);
    return result;
  }
};

template<typename OP, typename CONT, typename PRED>
void on_container(CONT & c, Pred & p)
{
  OP(c.begin(),c.end(),p);
}


bool noCodeGenerationRequested(declarations_map_type::value_type const & v)
{
  auto & methods = v.second.methods;
  on_container<std::remove_if>(methods, wrongName("doit"));
  on_container<std::remove_if>(methods, wrongSignature("void () const"));
  return (methods.size() == 1);
}


void hm()
{
  on_container<std::remove_if>(decls, noCodeGenerationRequested);
}


#include "clang-c/Index.h"
#include <iostream>


std::ostream & operator<<(std::ostream & os, CXString str)
{
  os << clang_getCString(str);
  return os;
}

CXChildVisitResult TranslationUnitVisitor(
    CXCursor cursor, CXCursor parent, CXClientData client_data)
{
  CXString spelling = clang_getCursorSpelling(cursor);
  std::cout << "@:" << spelling << std::endl;
  clang_disposeString(spelling);
  return CXChildVisit_Continue;
}

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
  CXLanguageKind language = clang_getCursorLanguage(cursor);
  std::cerr << "Language: " << nameOf_CXLanguageKind(language) << std::endl;
  clang_visitChildren(cursor, TranslationUnitVisitor, 0);
  clang_disposeTranslationUnit(translation);
  clang_disposeIndex(index);
  return 0;
}

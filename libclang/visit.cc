#include "libclang/data.hh"
#include "clang-c/Index.h"

/** Visitor to extract declarations and their contents from the libclang
 * AST.
 *
 * This visitor is traversing the AST, looking for declarations of C++
 * structures and classes and their fields and methods.
 * It is only considering the main file to
 * prevent traversal of the enormous AST generated in case of multiple
 * includes.
 *
 * Currently, templated classes or structures as well as unions
 * (templated or not) are ignored.
 *
 * There is not much processing apart from finding the relevant cursors
 * happening.
 *
 * @param client_data Must be a pointer to an instance
 * of @see declarations_map_type. The found declarations are stored inside
 * this instance.
 *
 * @todo Assert that the parent of a field or method is equal to its
 * semantic parent (the delcaration).
 * */
CXChildVisitResult translationUnitVisitor(
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
  // IMPORTANT: Use reference, otherwise a local copy is made and no
  // declarations are inserted into the provided map.
  auto & declarations = *((declarations_map_type *) client_data);
  if (kind == CXCursor_StructDecl
      || kind == CXCursor_ClassDecl)
  {
    return CXChildVisit_Recurse;
  }
  if (kind == CXCursor_FieldDecl)
  {
    declarations[parent].fields.insert(cursor);
  }
  else if (kind == CXCursor_CXXMethod)
  {
    declarations[parent].methods.insert(cursor);
  }
  return CXChildVisit_Continue;
}

/** Extract declarations using libclang.
 *
 * This function sets up libclang and runs the visitor
 * (@see translationUnitVisitor) to find all relevant declarations
 * and their contents. Those are returned to the caller.
 *
 * The arguments are passed directly to libclang.
 *
 * @todo Ensure that disposing the translation unit and the index
 * does not prevent use of the stored cursors.
 *
 * @todo Improve argument handling.
 *
 * @todo Implement error handling / logging.
 * */
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
    CXCursor cursor = clang_getTranslationUnitCursor(translation);
    clang_visitChildren(cursor, translationUnitVisitor, &declarations);
    clang_disposeTranslationUnit(translation);
  }
  clang_disposeIndex(index);
  return declarations;
}


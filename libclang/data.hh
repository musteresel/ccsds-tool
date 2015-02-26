/** Abstraction of gathered data from libclang.
 * */
#ifndef _CCSDS_TOOL_LIBCLANG_DATA_HH_
#define _CCSDS_TOOL_LIBCLANG_DATA_HH_ 1
#include "libclang/stdsupport.hh"
#include "clang-c/Index.h"
#include <set>
#include <map>

/** Contents of a declaration.
 *
 * This class holds cursors to fields and methods of a structure or class
 * declaration. No cursor to the actual declaration is contained within
 * this class.
 *
 * @todo Use a different kind of container, like a list, to enable better
 * ordering of fields.
 * */
struct DeclarationContent
{
  /** Container type used to store cursors to fields and methods.
   *
   * @todo Change, @see DeclarationContent.
   * */
  using container_type = std::set<CXCursor>;

  /** Cursors to every field contained within this declaration.
   * */
  container_type fields;

  /** Cursors to every method contained within this declaration.
   *
   * This container holds only methods of the delcaration, not
   * constructors or destructors.
   *
   * @todo Are operators recognized as method?
   * */
  container_type methods;
};

/** Maps the cursor of a declaration to its extracted relevant content.
 * */
using declarations_map_type = std::map<CXCursor, DeclarationContent>;

#endif


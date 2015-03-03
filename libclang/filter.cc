#include "libclang/filter.hh"
#include "libclang/data.hh"
#include "clang-c/Index.h"
#include <string>
#include <algorithm>

/** Creates a predicate function to match a method with given name
 * and signature.
 *
 * The returned function checks a CXCursor whether its spelling and
 * its type's spelling match the given name and signature. The
 * signature must match exactly, that is including whitespace.
 *
 * @warning Both const and volatile are recognized by this check.
 * @todo Improve whitespace handling in signature string.
 * @todo volatile is part of the signature. This may lead to unintended
 * missmatches.
 * */
auto const isMethod = [](std::string name, std::string signature)
{
  return [name, signature](CXCursor const & cursor)
  {
    CXType type = clang_getCursorType(cursor);
    CXString spelling = clang_getCursorSpelling(cursor);
    CXString type_spelling = clang_getTypeSpelling(type);
    bool result = (signature == clang_getCString(type_spelling))
      && (name == clang_getCString(spelling));
    clang_disposeString(spelling);
    clang_disposeString(type_spelling);
    return result;
  };
};

/** Predicate function to filter out map pairs which don't match the
 * requested name and signature.
 *
 * Takes a value_type (a pair normally) of a map between declaration
 * cursors and declaration contents (@see declarations_map_type).
 * If the declarations methods don't contain methods matching the
 * given name and signature, then no code shall be generated for that
 * declaration.
 *
 * @todo Is it possible that multiple methods match the name and
 * signature?
 * */
bool noCodeGenerationRequested(declarations_map_type::value_type & v)
{
  auto const & methods = v.second.methods;
  using std::find_if;
  using std::begin;
  using std::end;
  bool noSerializeMethod =
    end(methods) == find_if(begin(methods), end(methods),
        isMethod("serialize", "void (char *&) const"));
  bool noDeserializeMethod =
    end(methods) == find_if(begin(methods), end(methods),
        isMethod("deserialize", "void (char *&)"));
  return noSerializeMethod || noDeserializeMethod;
}


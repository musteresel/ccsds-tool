/** Filtering extracted declarations for the ones which require
 * code generation.
 * */
#ifndef _CCSDS_TOOL_LIBCLANG_FILTER_HH_
#define _CCSDS_TOOL_LIBCLANG_FILTER_HH_ 1
#include "libclang/data.hh"

bool noCodeGenerationRequested(declarations_map_type::value_type & v);

#endif

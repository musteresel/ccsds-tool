/** Abstraction of the extracted structure / class information.
 *
 * */
#ifndef _CCSDS_TOOL_OUTPUT_DATA_HH_
#define _CCSDS_TOOL_OUTPUT_DATA_HH_ 1
#include <string>
#include <forward_list>
#include <utility>

/** Contains information extracted from C++ struct and class definitions.
 *
 */
struct Structure
{
  /** Type of the container holding the field names.
   *
   * Providing the type as part of the API frees the user from changing
   * code in case this type gets changed.
   * */
  using fields_type = std::forward_list<std::string>;

  /** Name of the structure.
   *
   * @todo Implement namespace handling.
   * */
  std::string name;

  /** Field names of the structure.
   *
   * Contains the name of every field defined in that structure. Neither
   * the type nor the modifiers are represented, just plain names.
   *
   * @warning Currently the order of fields is formally unspecified, but
   * depending on the type (@see fields_type) the fields may be in the
   * same order when defined inside the source code.
   *
   * @todo Decide whether order of fields is part of this specification.
   * */
  fields_type fields;

  /** Perfect forwarding constructor, setting name and fields.
   *
   * @param n Initialization for the name.
   * @param f Initialization for the fields container.
   */
  template<typename NM, typename FLDS> Structure(NM&& n, FLDS&& f)
    : name(std::forward<NM>(n)), fields(std::forward<FLDS>(f))
  {}

  /** Perfect forwarding constructor, setting name only.
   *
   * The name (@see name) is initialized depending on the argument.
   * The fields container (@see fields) is default initialized.
   *
   * This constructor is explicit to prevent overload issues with copy
   * and move constructors.
   *
   * @param n Initialization for the name.
   * */
  template<typename NM> explicit Structure(NM && n)
    : name(std::forward<NM>(n))
  { /* default init fields */ }

  /** Default move constructor */
  Structure(Structure&&) = default;

  /** Default copy constructor */
  Structure(Structure const &) = default;

  /** No default constructor! */
  Structure() = delete;
};

#endif

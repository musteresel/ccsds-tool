/** Implementation of the actual generation of serialization code.
 * */
#include "output/serialization.hh"

/** Prints a serialization method for a given structure.
 *
 * This function prints C++ code to the given output stream. This code
 * serializes the associated C++ class, which is described by the given
 * Structure (@see Structure).
 *
 * @todo Change dummy name and signature of generated method.
 * */
void printSerializationMethod(std::ostream & o, Structure const & s)
{
  // Use \n instead of std::endl to prevent flushing of the buffer.
  o << "void " << s.name << "::serialize(char *& buffer) const {\n";
  for (auto field : s.fields)
  {
    o << "  ccsds_tool::serialize(buffer, " << field << ");\n";
  }
  o << "}\n";
}

void printDeserializationMethod(std::ostream & o, Structure const & s)
{
  o << "void " << s.name << "::deserialize(char *& buffer) {\n";
  for (auto field : s.fields)
  {
    o << "  ccsds_tool::deserialize(buffer, " << field << ");\n";
  }
  o << "}\n";
}

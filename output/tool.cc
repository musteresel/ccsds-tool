#include "data.hh"
#include "serialization.hh"
#include <iostream>
#include <algorithm>

int main(int argc, char ** argv)
{
  auto structures = {
    Structure("One", Structure::fields_type{"field"}),
    Structure("Two", Structure::fields_type{"feld", "undNochEines"})};
  std::for_each(std::begin(structures), std::end(structures),
      [] (Structure const & s) {
      printSerializationMethod(std::cout, s);});
  return 0;
}



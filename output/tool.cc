#include <iostream>
#include <string>
#include <forward_list>
#include <utility>

// list/set of decl

struct Field
{
  std::string const name;
  Field(Field &&) = default;
  Field(Field const &) = default;
  template<typename STR> explicit Field(STR&& n)
    : name(std::forward<STR>(n))
  {}
};

struct Decl
{
  using fields_type = std::forward_list<Field>;
  std::string const name;
  fields_type const fields;
  template<typename STR, typename VECT> Decl(STR&& n, VECT&& f)
    : name(std::forward<STR>(n)), fields(std::forward<VECT>(f))
  {}
};


class Declaration
{
  public:
    virtual void implement(std::ostream & os) const = 0;
};
class StructureDecl : public Declaration
{
  public:
    using fields_type = std::forward_list<Field>;
    std::string const name;
    fields_type const fields;
    template<typename STR, typename FLDS>
      StructureDecl(STR&& n, FLDS&& f)
      : name(std::forward<STR>(n)), fields(std::forward<FLDS>(f))
      {}
    void implement(std::ostream & os) const
    {
      os << "void " << name << "::doit(void) const {";
      for (auto field : fields)
      {
        os << "::doit(" << field.name << ");";
      }
      os << "}";
    }
};


void printSignature(std::ostream & os, Decl const & decl)
{
  os << "template<> void doit(" << decl.name << " const & v)";
}

void print(std::ostream & os, Decl const & decl)
{
  printSignature(os, decl);
  os << "{" << std::endl;
  for (auto field : decl.fields)
  {
    os << "  doit(v." << field.name << ");" << std::endl;
  }
  os << "}" << std::endl;
}






int main(int argc, char ** argv)
{
  auto f = Field("field");
  auto d = Decl("Decl", Decl::fields_type({f, Field("more"), Field("less")}));
  print(std::cout, d);

  StructureDecl("Str", StructureDecl::fields_type({f, Field("well")}))
    .implement(std::cout);
  std::cout << std::endl;
  return 0;
}


struct Structure
{
  using fields_type = std::forward_list<std::string>;
  std::string name;
  fields_type fields;
  template<typename NM, typename FLDS> Structure(NM&& n, FLDS&& f)
    : name(std::forward<NM>(n)), fields(std::forward<FLDS>(f))
  {}
  template<typename NM> Structure(NM && n)
    : name(std::forward<NM>(n))
  { /* default init fields */ }
};

void printSerializationMethod(std::ostream & o, Structure const & s)
{
  // Use \n instead of endl to prevent flushing
  o << "void " << s.name << "::doit(void) const {\n";
  for (auto field : s.fields)
  {
    o << "::doit(" << field << ");\n";
  }
  o << "}\n";
}

/*
 * TYPE: name, size, align
 * COMPLEX: fields, kind (product | sum)
 * FIELD: name + TYPE + offset
 *
 *
 * COMPOUND: has Type, fields, kind
 * PRIMITIVE: has Type
 *
 *
 * optionalTemplate
 *
 * printSignature (catches template stuff)
 *
 * field: name to call function on it.
 * */


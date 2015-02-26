

struct CStructure
{
  int a;
  int x : 4;
  struct CStructure * next;
} InstanceOfCStructure;

union CUnion
{
  int b;
  float c;
  char d;
} InstanceOfCUnion;

union CUnion AnotherInstanceOfCUnion;
struct CStructure AnotherInstanceOfCStructure;

class ExtClass;
class Simple
{
  public:
    int pub;
  protected:
    struct hmmm
    {
      int XX;
      int YY;
    } STRU;
    float prot;
  private:
    char priv;
} InstanceOfSimple;

class Complex
{
  ExtClass * pointer;
  Complex(int a)
  {
  }
  void stuff(Simple const &) const;
  int returningInt(void) const;
  char whatABoat(char const * const, Simple &);
};


struct SerializeMe
{
  int a;
  int b;
  int c;
  void doit() const;
};

class Me2
{
  private:
    int const WOAH;
  public:
    SerializeMe & thatGuy;
    void doit() const;
};

void dummy(void);

template<typename X>
class Templated
{
  X funny;
};
template<>
class Templated<Complex>
{
  int well_kind_of_strange;
  Templated<ExtClass const &> very_strange_indeed;
};


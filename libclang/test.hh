

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
};

void dummy(void);


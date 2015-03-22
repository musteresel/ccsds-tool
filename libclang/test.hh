
struct CStructure
{
  int a;
  int x : 4;
  struct CStructure * next;
} InstanceOfCStructure;

namespace NAMESPACE
{
  struct SerializeMe
  {
    int a;
    int b;
    int c;
    void serialize(char*&) const;
    void deserialize(char*&);
  };

  namespace INNER { namespace INNEST {
    struct JustSomeStruct
    {
      int blah;
      struct HereItGoes
      {
        int x;
        void serialize(char*&) const;
        void deserialize(char*&);
      };
    };
  }}
}

class Me2
{
  private:
    int const WOAH;
  public:
    NAMESPACE::SerializeMe & thatGuy;
    void serialize(char*&) const;
    void deserialize(char*&);
};



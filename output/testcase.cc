#include <iostream>


class Simple
{
  int a;
  float b[3];
  public:
  void doit(void) const;
};

union Hell
{
  int a;
  char b;
  void doit(void) const;
};

template<typename X> void doit(X const & x)
{
  std::cout << "STRUCT/CLASS" << std::endl;
  x.doit();
}
template<> void doit(int const &)
{
  std::cout << "INT" << std::endl;
}
template<> void doit(float const &)
{
  std::cout << "FLOAT" << std::endl;
}
template<std::size_t N, typename X> void doit(X(&array)[N])
{
  for (auto i = 0; i < N; i++)
  {
    doit(array[i]);
  }
}
/*
template<> void doit(Simple const & s)
{
  s.doit();
}
*/
void Simple::doit(void) const
{
  ::doit(a);
  ::doit(b);
}
void Hell::doit(void) const
{
  std::cout << "Welcome to HELL" << std::endl;
  // Select largest to serialize
  // TODO will this always work?
  ::doit(a);
  // Don't:
  // template<class A, class B> union Screwed { A a; B b; };
  //
  // Conversion to char[] won't help either, byte order might get screwed.
  // Don't serialize unions for now.
}

int main(int argc, char ** argv)
{
  auto s = Simple();
  auto u = Hell();
  doit(s);
  doit(u);
  return 0;
}


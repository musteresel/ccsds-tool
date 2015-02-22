#include <iostream>
using namespace std;

template<typename T> void doit(T const & t)
{
  cout << "NOIMPL" << endl;
}
template<> void doit(int const & i)
{
  cout << "INT: " << i << endl;
}
template<> void doit(float const & f)
{
  cout << "FLOAT: " << f << endl;
}


struct Simple
{
  int A;
  float B;
};

template<> void doit(Simple const & s)
{
  cout << "Simple {" << endl;
  doit(s.A);
  doit(s.B);
  cout << "}" << endl;
}


template<typename Y> struct OKEY
{
  Y y;
  Simple s;
};

template<typename T> void doit(OKEY<T> const & o)
{
  cout << "OKEY<T> {" << endl;
  doit(o.y);
  doit(o.s);
  cout << "}" << endl;
}

int main(int argc, char ** argv)
{
  Simple s = Simple();
  OKEY<int> o = OKEY<int>();
  doit(s);
  doit(o);
  return 0;
}



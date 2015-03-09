#include "debug-comma.hh"
#include "serialize.hh"

int main(int argc, char ** argv)
{
  using namespace ccsds_tool;
  auto buffer = new char[500];
  auto writePtr = buffer, readPtr = buffer;
  MyThing thing, copy;
  serialize(writePtr, thing);
  deserialize(readPtr, copy);
  return 0;
}


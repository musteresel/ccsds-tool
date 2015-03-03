#include "ccsds-tool/debug-comma.hh"
#include "serialize.hh"

int main(int argc, char ** argv)
{
  auto buffer = new char[500];
  auto writePtr = readPtr = buffer;
  MyThing thing, copy;
  serialize(writePtr, thing);
  deserialize(readPtr, copy);
  return 0;
}


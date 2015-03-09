#ifndef _TEST_SERIALIZE_H_
#define _TEST_SERIALIZE_H_ 1

#include "debug-comma.hh"

struct SubThing
{
  int value;
  void serialize(char *&) const;
  void deserialize(char *&);
};

struct MyThing
{
  int value;
  SubThing subThing;
  int more;
  void serialize(char *&) const;
  void deserialize(char *&);
};


#endif


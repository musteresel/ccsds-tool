#ifndef _TEST_SERIALIZE_H_
#define _TEST_SERIALIZE_H_ 1


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


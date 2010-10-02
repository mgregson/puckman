#ifndef __RANDOM_H__
#define __RANDOM_H__

class Random
{
private:
  unsigned int state;
public:
  int rand();
  void seed(int);
};

#endif

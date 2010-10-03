#ifndef __WORLD_H__
#define __WORLD_H__

#include "Random.h"

#define IN_BOUNDS(x) (0 <= x && x < width)

class Client;

class World
{
public:
  Client* current;
  Client* other;
  int width;
  char* grid;

  World(int, Client*, Client*);
  ~World();

  void generate(Random*);

  int getWidth();
  int move(int, int, int, int);
  void flip();
};

#endif

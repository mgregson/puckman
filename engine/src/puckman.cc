#include <stdlib.h>

#include "Client.h"
#include "Random.h"
#include "World.h"

int main(int argc, char** argv)
{
  int seed;
  Random rand;
  rand.seed(seed);
  int width = rand.rand();

  World world;
  world.generate(rand, 5);

  Client a;
  Client b;

  while(a.is_alive() && b.is_alive())
    {
      a.do_turn();
      b.do_turn();
    }

  a.print_score();
  b.print_score();
  exit(0);
}

#include <iostream>
#include <stdlib.h>

#include "Client.h"
#include "Random.h"
#include "World.h"

#include "defines.h"

void sad_panda()
{
  std::cerr << "Unhappy - needs some stuff to run!"
	    << std::endl;
  exit(5);
}

int main(int argc, char** argv)
{
  if(argc < 3)
    {
      sad_panda();
    }

  int seed;
  Random rand;
  rand.seed(seed);
  int width = rand.rand() % 200;

  World world(width);
  world.generate(&rand);

  Client a(argv[1]);
  Client b(argv[2]);

  while(a.live && b.live)
    {
      a.do_turn(&world);
      world.flip();
      b.do_turn(&world);
      world.flip();
    }

  if(a.live)
    a.score += SCORE_LASTMAN;

  if(b.live)
    b.score += SCORE_LASTMAN;

  a.print_score();
  b.print_score();
  exit(0);
}

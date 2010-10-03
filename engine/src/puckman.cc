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

  std::cout << width << std::endl;

  Client a(argv[1]);
  Client b(argv[2]);

  a.x = 10;
  a.y = 10;
  b.x = 3;
  b.y = 3;

  World world(width, &a, &b);
  world.generate(&rand);

  world.grid[a.x+(a.y*world.getWidth())] = 'C';
  world.grid[b.x+(b.y*world.getWidth())] = 'P';
  
  std::cout << "Starting contest" <<std::endl;

  while(a.live && b.live)
    {
      a.do_turn(&world);
      world.flip();
      if(!b.live) break;
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

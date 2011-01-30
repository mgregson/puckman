#include <iostream>
#include <stdlib.h>
#include <utility>
#include <list>

#include "Client.h"
#include "Random.h"
#include "World.h"
#include "Visualizer.h"

#include "defines.h"

struct point
{
  int x, y;
};

void sad_panda()
{
  std::cerr << "Unhappy - needs some stuff to run! (app1 app2 [visualizer])"
	    << std::endl;
  exit(5);
}

int main(int argc, char** argv)
{
  
  if(argc < 3)
    {
      sad_panda();
    }
  Visualizer * v = NULL;
  if (3 < argc) {
    v = new Visualizer(argv[3]);
  }

  int seed = 0;
  Random rand;
  rand.seed(seed);
  int width = rand.rand() % 200;

  std::cout << width << std::endl;

  Client a(argv[1]);
  Client b(argv[2]);

  World world = World(width, &a, &b);
  world.generate(&rand);

  point start;
  start.x = rand.rand() % width;
  start.y = rand.rand() % width;

  //bfs find reasonable start location
  std::list<point> tosee;
  point n;
  while(world.grid[start.x+(start.y*width)] == WALL)
    {
      if(start.x-1 >= 0)
	{
	  n.x = start.x-1;
	  n.y = start.y;
	  tosee.push_back(n);
	}
      if(start.x+1 < width)
	{
	  n.x = start.x+1;
	  n.y = start.y;
	  tosee.push_back(n);
	}
      if(start.y-1 >= 0)
	{
	  n.x = start.x;
	  n.y = start.y-1;
	  tosee.push_back(n);
	}
      if(start.y+1 < width)
	{
	  n.x = start.x;
	  n.y = start.y-1;
	}
      start = tosee.front();
      tosee.pop_front();
    }

  a.x = start.x;
  a.y = start.y;
  b.x = width - (start.x + 1);
  b.y = width - (start.y + 1);

  world.grid[a.x+(a.y*world.getWidth())] = 'C';
  world.grid[b.x+(b.y*world.getWidth())] = 'P';
  
  std::cout << "Starting contest" <<std::endl;
  
  int rounds = 0;
  while(a.live && b.live && rounds < ROUND_LIMIT)
    {
      a.do_turn(&world);
      world.flip();
      if (v != NULL)
	v->send_world(&world);
      if(!b.live) break;
      b.do_turn(&world);
      if (v != NULL)
	v->send_world(&world);
      world.flip();
      ++rounds;
    }

  if(a.live)
    {
      a.score += SCORE_LASTMAN;
      a.die();
    }

  if(b.live)
    {
      b.score += SCORE_LASTMAN;
      b.die();
    }

  a.print_score();
  b.print_score();
  if (v != NULL) {
    delete v;
  }
  exit(0);
}

#include <stdlib.h>
#include "World.h"

char random_unfill(Random* rand)
{
  return EMPTY;
}

void World::World(int width)
{
  grid = malloc(width*width);
}

void World::~World()
{
  free(grid);
}

void World::generate(Random* rand)
{
  for(int w = 0; w < width; w++)
    {
      for(int h = 0; i <= w; h++)
	{
	  grid[(width-h)+((width-w)*width)] = grid[h+(w*width)]
	    = random_unfill(rand);
	}
    }
}

int World::getWidth()
{
  return width;
}

int World::move(int x_1,
		int y_1,
		int x_2,
		int y_2)
{
  if(IN_BOUNDS(x_1)
     && IN_BOUNDS(y_1)
     && IN_BOUNDS(x_2)
     && IN_BOUNDS(y_2))
    {
      grix[x_2+(y_2*width)] = grid[x_1+(y_1*width)];
      grid[x_1+(y_1*width)] = EMPTY;
      return 0;
    }
  return 1;
}

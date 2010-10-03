#include <stdlib.h>
#include <string.h>
#include "World.h"
#include "Client.h"

#include "defines.h"

char random_unfill(Random* rand)
{
  if(float(rand->rand())/RAND_MAX > P_HOLLOW)
    return EMPTY;
  return WALL;
}

bool _clear_from(int sx,
		 int sy,
		 int max_x,
		 int max_y,
		 int min_x,
		 int min_y,
		 int gwidth,
		 char* grid,
		 char* seen)
{
  if(sx < min_x || sx > max_x || sy < min_y || sy > max_y
     || max_x >= gwidth || max_x < min_x)
    return false;
  if(grid[sx+(sy*gwidth)] != WALL)
    return true;

  seen[sx+(sy*gwidth)] = 1;
  if((sx-1 >= min_x && seen[sx-1+(sy*gwidth)] != 0 && _clear_from(sx-1, sy,
								  max_x, max_y,
								  min_x, min_y,
								  gwidth, grid,
								  seen))
     ||
     (sx+1 <= max_x && seen[sx+1+(sy*gwidth)] != 0 && _clear_from(sx+1, sy,
								  max_x, max_y,
								  min_x, min_y,
								  gwidth, grid,
								  seen))
     ||
     (sy-1 <= min_y && seen[sx+((sy-1)*gwidth)] != 0 && _clear_from(sx, sy-1,
								    max_x-1,
								    max_y,
								    min_x,
								    min_y,
								    gwidth,
								    grid,
								    seen))
     ||
     (sy+1 <= min_y && seen[sx+((sy+1)*gwidth)] != 0 && _clear_from(sx, sy+1,
								    max_x+1,
								    max_y,
								    min_x,
								    min_y,
								    gwidth,
								    grid,
								    seen)))
    {
      grid[sx+(sy*gwidth)] = EMPTY;
      grid[(gwidth-sx)+((gwidth-sy)*gwidth)] = EMPTY;
      return true;
    }
  return false;
}

void clear_from(int sx,
		int sy,
		int max_x,
		int max_y,
		int min_x,
		int min_y,
		int gwidth,
		char* grid)
{
  char* seen = (char*)malloc(gwidth*gwidth);
  memset(seen, 0, gwidth*gwidth);
  _clear_from(sx, sy, max_x, max_y, min_x, min_y, gwidth, grid, seen);
  free(seen);
  return;
}

World::World(int width,
	     Client* a,
	     Client* b)
{
  this->width = width;
  grid = (char*)malloc(width*width);
  memset((void*)grid, EMPTY, width*width);
  current = a;
  other = b;
}

World::~World()
{
  free(grid);
}

void World::generate(Random* rand)
{
  for(int w = 0; w < width; w++)
    {
      for(int h = 0; h <= w; h++)
	{
	  grid[(width-h)+((width-w)*width)] = grid[h+(w*width)]
	    = random_unfill(rand);
	}
    }

  //TODO: Ensure reachability
  for(int w = 0; w < width; w++)
    {
      for(int h = 0; h < w; h++)
	{
	  if(grid[w+(h*width)] != WALL)
	    {
	      clear_from(w, h, w, width, 0, 0, width, grid);
	    }
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
      grid[x_2+(y_2*width)] = grid[x_1+(y_1*width)];
      grid[x_1+(y_1*width)] = EMPTY;
      return 0;
    }
  return 1;
}

void World::flip()
{
  Client* t = current;
  current = other;
  other = t;

  grid[other->x+(other->y*width)] = other->state;
  grid[current->x+(current->y*width)] = current->state == SPUCK ? SSELF : SELF;
}



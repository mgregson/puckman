#include "stdio.h"
#include "puckman.h"

int main(int argc, char** argv)
{
  init();
  while(read_world() > 0)
    {
      if(IN_BOUNDS(pos_x-1,pos_y) && CELL(pos_x-1,pos_y) != WALL)
	{
	  left();
	}
      else if(IN_BOUNDS(pos_x,pos_y-1) && CELL(pos_x,pos_y-1) != WALL)
	{
	  up();
	}
      else if(IN_BOUNDS(pos_x+1,pos_y) && CELL(pos_x+1,pos_y) != WALL)
	{
	  right();
	}
      else
	{
	  down();
	}
    }
  cleanup();
  fprintf(stderr, "Exiting\n");
  return 0;
}

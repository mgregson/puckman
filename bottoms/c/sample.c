#include "stdio.h"
#include "puckman.h"

int main(int argc, char** argv)
{
  init();
  while(read_world() > 0)
    {
      if(pos_x >= 1 && CELL(pos_x-1,pos_y) != WALL)
	{
	  left();
	}
      else if(pos_y >= 1 && CELL(pos_x,pos_y-1) != WALL)
	{
	  up();
	}
      else if(pos_x+1 < width && CELL(pos_x+1,pos_y) != WALL)
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

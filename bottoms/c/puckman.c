#include <unistd.h>
#include <stdio.h>

#include "puckman.h"

int* grid;
int width;
int pos_x;
int pos_y;

void error(char* str)
{
  fprintf(stderr, "%s", str);
  fflush(stderr);
}

void init()
{
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
}

int read_world()
{
  int i = 0;
  int j = 0;
  int tries = 0;
  int r = scanf("%d", &width);
  if(r != 1)
    {
      error("Can't read width: %d\n");
      return 0;
    }

  for(i = 0; i < width; ++i)
    {
      tries = 0;
      r = 0;
      do
	{
	  r = read(0, &grid[i*width], width);
	}
      while(r < width && tries < 5);
      if(tries >= 5)
	{
	  error("Can't read grid.\n");
	  return 0;
	}
    }

  for(i = 0; i < width; ++i)
    {
      for(j = 0; j < width; ++j)
	{
	  if((grid[i+(j*width)] == SELF)
	     || (grid[i+(j*width)] == SSELF))
	    {
	      pos_x = i;
	      pos_y = j;
	      continue;
	    }
	  if((grid[i+(j*width)] == PUCK)
	     || (grid[i+(j*width)] == SPUCK))
	    {
	      epos_x = i;
	      epos_y = j;
	    }
	}
    }
  return 1;
}

void left()
{
  printf("L");
}

void right()
{
  printf("R");
}

void up()
{
  printf("U");
}

void down()
{
  printf("D");
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "puckman.h"

char* grid = 0;
int width;
int pos_x;
int pos_y;
int epos_x;
int epos_y;

char access_cell (int x , int y) {
  return grid[x+(y*width)];
}

int check_in_bounds (int x , int y) {
  return (0 <= x && x < width && 0 <= y && y < width);
}

void error(char* str)
{
  fprintf(stderr, "%s", str);
  fflush(stderr);
}

void init()
{
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  width = 0;
}

void cleanup()
{
  if(grid)
    free(grid);
  grid = 0;
}

int read_world()
{
  int i = 0;
  int j = 0;
  int tries = 0;
  int r;
  if(width == 0)
    {
      do
	{
	  r = fgetc(stdin);
	  if(r < '0' || r > '9') continue;
	  width = width*10;
	  width += (r-'0');
	}
      while(r != '\n');
      grid = (char*)malloc(width*width);
    }
  else
    do
      {
	r = fgetc(stdin);
      }
    while(r != '\n');
    r = 0;
  while(r < width*width && tries < 10)
    {
      j = read(0, &grid[r], width*width-r);
      if(j < 0)
	{
	  error("Reading is bad.\n");
	  return 0;
	}
      if(j == 0)
	{
	  error("Unexpected EOF.\n");
	  return 0;
	}
      fprintf(stderr, "Read %d bytes: %d, %d\n", j, r, width*width);
      r += j;
      ++tries;
    }
  if(tries >= 10)
    {
      fprintf(stderr, "Reading grid: %d,%d\n", i, r);
      error("Can't read grid.\n");
      return 0;
    }
  getchar();

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
  write(fileno(stdout), "L", 1);
}

void right()
{
  write(fileno(stdout), "R", 1);
}

void up()
{
  write(fileno(stdout), "U", 1);
}

void down()
{
  write(fileno(stdout), "D", 1);
}

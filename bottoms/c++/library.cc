#include <unistd.h>
#include <stdio.h>
#include "puckman.h"

PuckmanWorld::PuckmanWorld(Puckman* p,
			   PuckmanCharacter* c)
{
  puck = p;
  other = c;
  grid = NULL;
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
}

PuckmanWorld::~PuckmanWorld()
{
  if(grid)
    delete grid;
}

void PuckmanWorld::run()
{
  while(update())
    {
      switch(puck->makeMove(this))
	{
	case LEFT:
	  printf("L");
	  break;
	case RIGHT:
	  printf("R");
	  break;
	case UP:
	  printf("U");
	  break;
	case DOWN:
	  printf("D");
	  break;
	}
    }
}

bool PuckmanWorld::update()
{
  int tries = 0;
  int r = scanf("%d", &width);
  if(r != 1)
    {
      return false;
    }
  if(!grid)
    grid = new char[width*width];
  for(int i = 0; i < width; ++i)
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
	  return false;
	}
    }

  for(int i = 0; i < width; ++i)
    {
      for(int j = 0; j < width; ++j)
	{
	  if((grid[i+(j*width)] == SELF)
	     || (grid[i+(j*width)] == SSELF))
	    {
	      puck->x = i;
	      puck->y = j;
	      if(grid[i+(j*width)] == SSELF)
		puck->state = SUPER;
	      else puck->state = NORMAL;
	      continue;
	    }
	  if((grid[i+(j*width)] == PUCK)
	     || (grid[i+(j*width)] == SPUCK))
	    {
	      other->x = i;
	      other->y = j;
	      if(grid[i+(j*width)] == SPUCK)
		other->state = SUPER;
	      else other->state = NORMAL;
	    }
	}
    }
  return true;
}

char PuckmanWorld::operator[](const int idx)
{
  return grid[idx];
}

PuckmanCharacter* PuckmanWorld::getOponent()
{
  return other;
}

PuckmanCharacter::PuckmanCharacter()
{
  x = y = 0;
  state = NORMAL;
}

PuckmanCharacter::~PuckmanCharacter()
{
}

bool PuckmanCharacter::isSuper()
{
  return state == SUPER;
}

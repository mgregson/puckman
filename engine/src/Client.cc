#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <iostream>
#include <sys/select.h>

#include "Client.h"

#include "defines.h"

Client::Client(char* cmd)
{
  live = false;
  countdown = 0;
  x = 0;
  y = 0;
  score = 0;

  FD_ZERO(&readset);

  timeout.tv_usec = 0;
  timeout.tv_sec = 60;

  int readpipe[2];
  int writepipe[2];
  int waitpipe[2];

  if(pipe(readpipe))
    {
      std::cerr << "Failed to create read pipe!"
		<< std::endl;
      perror("Client.cc");
      exit(1);
    }
  if(pipe(writepipe))
    {
      std::cerr << "Failed to create write pipe!"
		<< std::endl;
      perror("Client.cc");
      exit(2);
    }
  if(pipe(waitpipe))
    {
      std::cerr << "Failed to create wait pipe!"
		<< std::endl;
      perror("Client.cc");
      exit(2);
    }

  if(pid = fork())
    {
      if(pid < 0)
	{
	  std::cerr << "Unable to fork!"
		    << std::endl;
	  perror("Client.cc");
	  exit(3);
	}

      close(writepipe[0]);
      close(readpipe[1]);
      kidin = fdopen(readpipe[0], "r");
      if(!kidin)
	{
	  std::cerr << "Can't open kidin fd!"
		    << std::endl;
	  perror("Client.cc");
	  exit(6);
	}
      kidout = fdopen(writepipe[1], "w");
      if(!kidout)
	{
	  std::cerr << "Can't open kidout fd!"
		    << std::endl;
	  perror("Client.cc");
	  exit(7);
	}

      setvbuf(kidin, NULL, _IONBF, 0);
      setvbuf(kidout, NULL, _IONBF, 0);

      int foo = 1;
      write(waitpipe[1], &foo, 1);
      close(waitpipe[0]);
      close(waitpipe[1]);

      FD_SET(fileno(kidin), &readset);

      live = true;
    }
  else
    {
      close(writepipe[1]);
      close(readpipe[0]);

      dup2(writepipe[0], 0);
      dup2(readpipe[1], 1);

      int foo;
      read(waitpipe[0], &foo, 1);
      close(waitpipe[0]);
      close(waitpipe[1]);

      execv(cmd, NULL);
      exit(4);
    }
}

Client::~Client()
{
  if(live) die();
}

void Client::do_turn(World* world)
{
  if(countdown <= 0)
    {
      countdown = 0;
      world->grid[x+(y * world->getWidth())] = SELF;
      state = PUCK;
    }
  send_world(world);
  char action = read_action();
  int dx = x, dy = y;
  std::cerr << action << std::endl;
  switch(action)
    {
    case 'L':
      dx -= 1;
      break;
    case 'R':
      dx += 1;
      break;
    case 'U':
      dy -= 1;
      break;
    case 'D':
      dy += 1;
      break;
    default:
      std::cerr << "Unknown command from client"
		<< " - death is the only "
		<< "path to redemption."
		<< std::endl;
      die();
      return;
    }
  check_and_move(dx, dy, world);
  if(countdown > 0)
    countdown --;
}

char Client::read_action()
{
  /*
  if(select(1, &readset, 0, 0, &timeout) <= 0)
    {
      die();
      return '~';
    }
  */
  char r = '~';
  read(fileno(kidin), &r, 1);
  return r;
}

void Client::send_world(World* world)
{
  int outbs = 0;
  int d = 0;
  int e = 0;
  int tries = 0;
  fprintf(kidout, "%d\n", world->getWidth());
  for(int i = 0; i < world->getWidth(); i++)
    {
      write(1, &world->grid[i*world->getWidth()], world->getWidth());
      std::cout << std::endl;
    }

  while(outbs < world->getWidth()*world->getWidth())
    {
      d = write(fileno(kidout),
		&world->grid[outbs],
		world->getWidth()*world->getWidth()-outbs);
      if(d < 0)
	e++;
      else
	outbs += d;
      std::cerr << "Wrote " << d << " bytes." << std::endl;
	  
      if(e >= 3 || ++tries > 10)
	{
	  std::cerr << "Error writing to "
		    << "child process.  "
		    << "Terminating..."
		    << std::endl;
	  die();
	  break;
	}
    }
  write(fileno(kidout), "\n", 1);
}

void Client::check_and_move(int dx,
			    int dy,
			    World* world)
{
  int width = world->getWidth();
  char* grid = world->grid;
  int offs = dx+(dy*width);
  if(!IN_BOUNDS(dx) || !IN_BOUNDS(dy)
     || grid[offs] == WALL)
    {
      std::cerr << "Illegal action!"
		<< std::endl;
      die();
      return;
    }

  switch(grid[offs])
    {
    case PILL:
      score += 2;
      grid[offs] = state = 'S';
      break;
    case DOT:
      score++;
      break;
    case PUCK:
      if(state == SPUCK)
	{
	  world->other->die();
	}
      else
	{
	  world->other->die();
	  die();
	}
      break;
    case SPUCK:
      if(state == SPUCK)
	{
	  world->other->die();
	}
      die();
      break;
    case GHOST:
      die();
      break;
    default:
      break;
    }
  world->move(x,y,dx,dy);
  x = dx;
  y = dy;
}

void Client::print_score()
{
  std::cout << score << std::endl;
}

void Client::die()
{
  live = false;
  kill(pid, 9);
}

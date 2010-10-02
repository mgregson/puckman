#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include "Client.h"

void Client::Client(std::string cmd)
{
  live = false;

  int readpipe[2];
  int writepipe[2];

  if(pipe(readpipe))
    {
      std::cerr << "Failed to create read pipe!"
		<< std::endl;
      perror();
      exit(1);
    }
  if(pipe(writepipe))
    {
      std::cerr << "Failed to create write pipe!"
		<< std::endl;
      perror();
      exit(2);
    }

  if(pid = fork())
    {
      if(pid < 0)
	{
	  std::cerr << "Unable to fork!"
		    << std::endl;
	  perror();
	  exit(3);
	}

      //We are the parent
      close(writepipe[0]);
      close(readpipe[1]);
      kidin = readpipe[0];
      kidout = writepipe[1];

      live = true;
    }
  else
    {
      close(writepipe[1]);
      close(readpipe[0]);

      dup2(writepipe[0], 1);
      dup2(readpipe[1], 0);

      execv(cmd, NULL);
      exit(4);
    }
}

void Client::do_turn(World* world)
{
  send_world(world);
  char action = read_action();
  int dx = x, dy = y;
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
}

void Client::send_world(World* world)
{
  for(int i = 0; i < world->width; i++)
    {
      std::cout.write(world->grid,
		      world->width);
      std::cout << std::endl;

      //TODO: Also write this shit to the client
      int outbs = 0;
      int d = 0;
      int e = 0;
      int tries = 0;
      while(outbs < width)
	{
	  d = write(kidout,
		    world->grid,
		    world->width);
	  if(d < 0)
	    e++;
	  else
	    outbs += d;
	  
	  if(e >= 3 || ++tries > 10)
	    {
	      std::cerr << "Error writing to "
			<< "child process.  "
			<< "Terminating..."
			<< std::endl;
	      die();
	    }
	}
    }
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
      break;
    case DOT:
      score++;
      break;
    }
}

void Client::print_score()
{
  std::cout << score << std::endl;
}

void Client::die()
{
  kill(pid, 9);
  live = false;
}

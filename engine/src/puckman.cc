#include <iostream>
#include <stdlib.h>
#include <utility>
#include <list>
#include <string>
#include <string.h>

#include <getopt.h>

#include "Client.h"
#include "Random.h"
#include "World.h"
#include "Visualizer.h"
#include "Logger.h"
#include "defines.h"

struct point
{
  int x, y;
};

int main(int argc, char** argv)
{
  
  //Extract the options
  static struct option long_options [] = {
    {"contestants",required_argument,NULL,'c'},
    {"visualizer",required_argument,NULL,'v'},
    {"logger",required_argument,NULL,'l'},
    {0, 0, 0, 0}
  };
  char ch;
  int long_opt_index = 0;
  std::string player1_program,player2_program,visualizer_program,log_file;
  char * players;
  while ((ch = getopt_long(argc,argv,"cvl",long_options,&long_opt_index)) != -1) {
    switch(ch) {
    case 'c':
      players = strtok(optarg," ");
      player1_program = players;
      strtok(NULL , " ");
      if (players == NULL) {
	std::cerr << "Require two players!" << std::endl;
	exit(-1);
      }
      player2_program = players;
      break;
    case 'v':
      visualizer_program = optarg;
      break;
    case 'l':
      log_file = optarg;
      break;
    }
  }
  if (player1_program == "" || player2_program == "") {
    std::cerr << "Please specifiy players with --contestants [player1] [player2]" << std::endl;
    exit(1);
  }
  //Random stuff
  int seed = 0;
  Random rand;
  rand.seed(seed);
  int width = rand.rand() % 200;

  std::cout << width << std::endl;

  Client a(player1_program.c_str());
  Client b(player2_program.c_str());

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

  Visualizer * v = NULL;
  if (visualizer_program != "") {
    std::cout << "Starting visualizer" << std::endl;
    v = new Visualizer(visualizer_program.c_str());
  }

  Logger * l = NULL;
  if (log_file != "") {
    std::cout << "Logging output to " << log_file << std::endl;
    l = new Logger(log_file.c_str());
  }
  
  int rounds = 0;
  while(a.live && b.live && rounds < ROUND_LIMIT)
    {
      a.do_turn(&world);
      world.flip();
      if (v != NULL) {
	v->send_world(a.score,b.score,&world);
      }
      if(!b.live) break;
      b.do_turn(&world);
      if (v != NULL) {
	v->send_world(a.score,b.score,&world);
      }
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

  if (v != NULL) {
    delete v;
  }
  a.print_score();
  b.print_score();
  exit(0);
}

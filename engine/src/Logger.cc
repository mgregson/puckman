#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <iostream>
#include <sys/select.h>

#include "Logger.h"

#include "defines.h"

Logger::Logger(const char* file)
{
  log_stream.open(file);
}

Logger::~Logger()
{
  log_stream.close();
}

//Assumes its called in the correct order cause I'm lazy
void Logger::do_move(int score,char move, std::string dtls)
{
  log_stream << move << std::endl;
  log_stream << dtls << std::endl;
  log_stream << score << std::endl;
}
void Logger::send_world(int p1id, int p2id,World * world) {
  //Send what the world is going to be
  log_stream << "#World width" << std::endl;
  log_stream << world->getWidth() << " " << world->getWidth() << std::endl;
  //Number of players
  log_stream << "# Number of players" << std::endl;
  log_stream << 2 << std::endl;
  //Find player locations
  int p1x,p1y,p2x,p2y;
  for (int i = 0 ; i < world->getWidth()*world->getWidth(); i++) {
    if (world->grid[i] == 'C') {
      p1x = i/world->getWidth();
      p1y = i%world->getWidth();
    }
    if (world->grid[i] == 'P') {
      p2x = i/world->getWidth();
      p2y = i%world->getWidth();
    }
  }
  log_stream << "#Player IDs & locations" << std::endl;
  log_stream << p1id << " " << p1x << " " << p1y << std::endl;
  log_stream << p2id << " " << p2x << " " << p2y << std::endl;
  log_stream << "#Number of ghosts" << std::endl;
  //Number of ghosts is 0 for now
  log_stream << 0 << std::endl;
  for(int i = 0; i < world->getWidth()*world->getWidth(); i++)
    {
      log_stream << world->grid[i];
      if (i % world->getWidth() == 0 && i != 0)
	std::cout << std::endl;
    }

}

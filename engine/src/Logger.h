#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include "World.h"

class Logger
{
private:
  std::ofstream log_stream;
public:
  void send_world(int player_1_id ,int player_2_id ,World*);
  void do_move (int score,char move,std::string dtls);
  Logger(const char*);
  ~Logger();
};

#endif

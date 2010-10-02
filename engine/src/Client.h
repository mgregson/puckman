#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <string>
#include <unistd.h>
#include "World.h"

class Client
{
private:
  char state;
  int x, y;
  int score;
  pid_t pid;
  int kidin, kidout;
  bool live;
  void send_world(World*);
  int read_action();
  void check_and_move(int, int);
public:
  Client(std::string);
  ~Client();
  void do_turn(World*);
  void print_score();
};

#endif

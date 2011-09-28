#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include "World.h"

class Client
{
public:
  char state;
  int x, y;
  bool live;
  int score;
  int countdown;

private:
  pid_t pid;
  FILE* kidin;
  FILE* kidout;
  fd_set readset;
  timeval timeout;
  void send_world(World*);
  char read_action();
  void check_and_move(int, int, World*);

public:
  Client(const char*);
  ~Client();
  void do_turn(World*);
  void print_score();
  void die();
};

#endif

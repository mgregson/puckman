#ifndef __VISUALIZER_H__
#define __VISUALIZER_H__

#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include "World.h"

class Visualizer
{
private:
  pid_t pid;
  FILE* kidin;
  FILE* kidout;
public:
  void send_world(int a,int b,World*);
  Visualizer(const char*);
  ~Visualizer();
};

#endif

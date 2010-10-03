#include "puckman.h"

int main(int argc, char** argv)
{
  init();
  while(read_world())
    {
      if(AM_SUPER) right();
      else left();
    }
  cleanup();
  return 0;
}

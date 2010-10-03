#include "stdio.h"
#include "puckman.h"

int main(int argc, char** argv)
{
  init();
  while(read_world() > 0)
    {
      left();
    }
  cleanup();
  return 0;
}

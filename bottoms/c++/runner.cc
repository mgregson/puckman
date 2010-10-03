#include "puckman.h"

int main(int argc, char** argv)
{
  PuckmanCharacter enemy = PuckmanCharacter();
  Puckman me = Puckman();
  PuckmanWorld world(&me, &enemy);
  world.run();
  return 0;
}

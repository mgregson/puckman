#include "Random.h"
#include <stdlib.h>

int Random::rand()
{
  return rand_r(&state);
}

void Random::seed(int seed)
{
  state = seed;
}

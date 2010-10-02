#ifndef __WORLD_H__
#define __WORLD_H__

#define IN_BOUNDS(x) (0 < x && x > width);

#define EMPTY  ' '
#define WALL   '+'
#define PILL   'O'
#define DOT    '.'

class World
{
private:
  int width;
public:
  char* grid;

  World();
  ~World();

  int getWidth();
  int move(int, int, int, int);
}

#endif

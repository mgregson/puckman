#ifndef __PUCKMAN_H__
#define __PUCKMAN_H__

#define CELL(x,y) grid[x+(y*width)]

extern int width;
extern int[] grid;

void init();
int read_world();
void left();
void right();
void up();
void down();

#endif

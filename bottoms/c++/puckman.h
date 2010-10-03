#ifndef __PUCKMAN_H__
#define __PUCKMAN_H__

#define EMPTY  ' '
#define WALL   '+'
#define PILL   'O'
#define DOT    '.'
#define GHOST  '&'
#define SELF   'C'
#define SSELF  '@'
#define PUCK   'P'
#define SPUCK  'S'

class PuckmanCharacter;
class Puckman;

class PuckmanWorld
{
private:
  char* grid;
  int width;
  Puckman* puck;
  PuckmanCharacter* other;
public:
  PuckmanWorld(Puckman*, PuckmanCharacter*);
  virtual ~PuckmanWorld();
  virtual void run();
  virtual bool update();
  virtual PuckmanCharacter* getOponent();
  virtual char operator[](const int);
};

enum Move
  { LEFT, RIGHT, UP, DOWN };
enum State
  { NORMAL, SUPER };

class PuckmanCharacter
{
protected:
  int x, y;
  State state;
public:
  PuckmanCharacter();
  virtual ~PuckmanCharacter();
  virtual bool isSuper();
  friend bool PuckmanWorld::update();
};

class Puckman : public PuckmanCharacter
{
public:
  Puckman();
  virtual ~Puckman();
  virtual Move makeMove(const PuckmanWorld*);
};

#endif

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>
class Actor; 
class Peach; 

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool isBlockingObjectAt(int x,int y);
  bool bonkObjectAt(int x, int y);
  void updateScore(int x);
  Peach* getPeach();
private:
	std::vector<Actor*> m_actors;
	Actor* peach;
	int score;
};

#endif // STUDENTWORLD_H_

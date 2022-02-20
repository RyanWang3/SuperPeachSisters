#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>
class Actor; 

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool isBlockingObjectAt(int x,int y);
private:
	std::vector<Actor*> m_actors;
	Actor* peach;

};

#endif // STUDENTWORLD_H_

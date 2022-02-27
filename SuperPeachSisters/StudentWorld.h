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
  // Record that a level was finished.  The parameter is true if it was
  // the last level.
  void endLevel(bool isGameWon);
  bool isBlockingObjectAt(int x,int y);
  bool bonkObjectAt(int x, int y, bool isPeachInvincible);
  bool overlapsPeach(int x, int y); 
  bool overlapsEnemy(int x, int y);
  void updateScore(int x);
  std::vector<Actor*>* getActors() { return &m_actors; }
  Peach* getPeach();
  void addActor(Actor* a);


private:
	std::vector<Actor*> m_actors;
	Actor* peach;
	int score;
	int status;
};

#endif // STUDENTWORLD_H_

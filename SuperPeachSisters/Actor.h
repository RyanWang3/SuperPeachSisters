#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"



class Actor : public GraphObject {
public:
	Actor(const int ID, StudentWorld* sw, int x, int y, int dir = 0, int depth = 0, double size = 1.0);
	virtual ~Actor(); 
	virtual void doSomething() = 0;
	virtual void bonk() {};
	StudentWorld* getWorld() { return m_world; }
	bool isAlive() { return m_alive; }
	void setDead() { m_alive = false; }
private:
	StudentWorld* m_world;
	bool m_alive; 
	
};

class Powerup : public Actor {
public:
	Powerup(StudentWorld* sw, int x, int y, int ID, int points);
	virtual void doSomething();
private:
	int point_value; 
};

const int POWERUP_NONE = 0;
const int POWERUP_STAR = 1;
const int POWERUP_FLOWER = 2;
const int POWERUP_MUSHROOM = 3; 

class Block : public Actor
{
public:
	Block(StudentWorld* sw, int x, int y);
	Block(StudentWorld* sw, int x, int y, int power);
	virtual void doSomething();

private:
	int powerup;
	bool powerup_released;
};

class Pipe : public Actor
{
public:
	Pipe(StudentWorld* sw, int x, int y);
	virtual void doSomething();


private:
};

class Peach : public Actor
{
public:
	Peach(StudentWorld* sw, int x, int y);
	virtual void doSomething();
	void updatePower(int powerUp);
	void updateHP(int hitpts) { hp = hitpts; }


private:
	int hp;
	int invincibility_ticks;
	bool invincibility_status;
	int powers; 
};
#endif // ACTOR_H_

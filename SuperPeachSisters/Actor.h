#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"



class Actor : public GraphObject {
public:
	Actor(const int ID, StudentWorld* sw, int x, int y, int dir = 0, int depth = 0, double size = 1.0);
	virtual ~Actor(); 
	virtual void doSomething() = 0;
	virtual void bonk() {}
	StudentWorld* getWorld() { return m_world; }
	bool isAlive() { return m_alive; }
	void setDead() { m_alive = false; }
private:
	StudentWorld* m_world;
	bool m_alive; 
	
};

class Goodie : public Actor {
public:
	Goodie(StudentWorld* sw, int x, int y, int ID, int points);
	virtual void doSomething();
private:
	int point_value; 
};

const int POWERUP_NONE = 0;
const int POWERUP_STAR = 1;
const int POWERUP_FLOWER = 2;
const int POWERUP_MUSHROOM = 3; 

class Obstacle : public Actor {
public:
	Obstacle(const int ID, StudentWorld* sw, int x, int y);
	virtual void doSomething(){}
};

class Block : public Obstacle
{
public:
	Block(StudentWorld* sw, int x, int y);
	Block(StudentWorld* sw, int x, int y, int power);

private:
	int powerup;
	bool powerup_released;
};

class Pipe : public Obstacle
{
public:
	Pipe(StudentWorld* sw, int x, int y);
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
	bool has_flower;
	bool has_mushroom;
	bool has_star;
	int remaining_star_ticks;

};
#endif // ACTOR_H_

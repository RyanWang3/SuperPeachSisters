#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

class Actor : public GraphObject {
public:
	Actor(const int ID, StudentWorld* sw, int x, int y, int dir = 0, int depth = 0, double size = 1.0);
	virtual ~Actor(); 
	virtual void doSomething() = 0;
	StudentWorld* getWorld() { return m_world; }
	bool isAlive() { return m_alive; }
private:
	StudentWorld* m_world;
	bool m_alive; 
	
};

class Twinkler : public Actor
{
public:
	Twinkler(StudentWorld* sw, int x, int y);
	virtual void doSomething();

private:
};

class Block : public Actor
{
public:
	Block(StudentWorld* sw, int x, int y);
	virtual void doSomething();

private:
};

class Peach : public Actor
{
public:
	Peach(StudentWorld* sw, int x, int y);
	virtual void doSomething();

private:
	int hp;
	bool invincibility;
	int powers; 
};
#endif // ACTOR_H_

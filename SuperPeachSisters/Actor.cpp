#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

/*Actor class*/
Actor::Actor(int ID, StudentWorld* sw, int x, int y, int dir, int depth, double size):
GraphObject(ID, x, y,dir,depth,size), m_world(sw),m_alive(true)
{

}

Actor::~Actor() {
}
/*Twinkler class*/

Twinkler::Twinkler(StudentWorld* sw, int x, int y)
	: Actor(IID_STAR, sw, x, y)
{
}

void Twinkler::doSomething()
{
	int key;
	if (getWorld()->getKey(key))
	{
		switch (key)
		{
		case KEY_PRESS_SPACE:
			getWorld()->playSound(SOUND_PLAYER_JUMP);
			break;
		}
	}
}

/*Block class*/

Block::Block(StudentWorld* sw, int x, int y)
	: Actor(IID_BLOCK, sw, x, y,0,2,1.0)
{
}

void Block::doSomething()
{

}


/*Peach class*/

Peach::Peach(StudentWorld* sw, int x, int y)
	: Actor(IID_PEACH, sw, x, y),hp(1),invincibility(false),powers(0)
{
}

void Peach::doSomething()
{
	if (!isAlive()) {
		return;
	}

}

#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
using namespace std; 
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

/*Pipe class*/

Pipe::Pipe(StudentWorld* sw, int x, int y)
	: Actor(IID_PIPE, sw, x, y, 0, 2, 1.0)
{
}

void Pipe::doSomething()
{

}

/*Peach class*/

Peach::Peach(StudentWorld* sw, int x, int y)
	: Actor(IID_PEACH, sw, x, y),hp(1),invincibility_ticks(0),invincibility_status(false),powers(0)
{
}

void Peach::doSomething()
{
	//step 1
	if (!isAlive()) {
		return;
	}
	//step 2
	if (invincibility_status==true&&invincibility_ticks>0) {
		invincibility_ticks--;
	}
	else if(invincibility_ticks==true && invincibility_ticks==0){
		invincibility_status = false; 
	}

	//Step 8
	int target_x=getX();
	int target_y=getY();
	int key;
	if (getWorld()->getKey(key))
	{
		switch (key)
		{
			
		case KEY_PRESS_LEFT:
			setDirection(180);
			target_x -= 4;
			if (getWorld()->isBlockingObjectAt(target_x, target_y)) {
				return;
			}
			moveTo(target_x, target_y);
			break;
		case KEY_PRESS_RIGHT:
			setDirection(0);
			target_x += 4;
			if (getWorld()->isBlockingObjectAt(target_x, target_y)) {
				return;
			}
			moveTo(target_x, target_y);
			break;
		}

	}
}

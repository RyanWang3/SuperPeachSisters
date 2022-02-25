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


/*Block class*/

Block::Block(StudentWorld* sw, int x, int y)
	: Actor(IID_BLOCK, sw, x, y,0,2,1.0), powerup(POWERUP_NONE),powerup_released(false)
{
}

Block::Block(StudentWorld* sw, int x, int y,int powerup)
	: Actor(IID_BLOCK, sw, x, y, 0, 2, 1.0), powerup(powerup), powerup_released(false)
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
	: Actor(IID_PEACH, sw, x, y),hp(1),invincibility_ticks(0),invincibility_status(false),powers(POWERUP_NONE)
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
	else if(invincibility_status==true && invincibility_ticks==0){
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

void Peach::updatePower(int powerUp) {
	powers = powerUp; 
}

//powerup class
Powerup::Powerup(StudentWorld* sw, int x, int y, int ID,int points)
	: Actor(ID, sw, x, y, 0, 1, 1.0), point_value(points)
{
}

void Powerup::doSomething() {
	getWorld()->updateScore(point_value); 
	getWorld()->getPeach()->updatePower(POWERUP_FLOWER);
	getWorld()->getPeach()->updateHP(2);
	setDead();
	getWorld()->playSound(SOUND_PLAYER_POWERUP);
	return;


}
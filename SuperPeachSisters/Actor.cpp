#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
using namespace std; 
/*Actor class*/
Actor::Actor(int ID, StudentWorld* sw, int x, int y, int dir, int depth, double size,bool blocksmovement):
GraphObject(ID, x, y,dir,depth,size), m_world(sw),m_alive(true),blockMovement(blocksmovement)
{

}

Actor::~Actor() {
}

void Actor::reverseDirection() {
	if (getDirection() == left) {
		setDirection(right);
	}
	else {
		setDirection(left);
	}
}
void Actor::converDirectionAndDistanceToXY(int dir, int dist, int& destx, int& desty) const {
	destx = getX();
	desty = getY(); 
	switch (dir) {
	case up:
		desty=getY() + dist;
		break;
	case down:
		desty = getY() - dist;
		break;
	case left:
		destx = getX() - dist;
		break;
	case right:
		destx =getX()+ dist; 
	}
	
}

void Actor::fallIfPossible(int dist) {
	int target_x = getX();
	int target_y = getY();
	for (int i = 0; i <= 3; i++) {
		if (getWorld()->isBlockingObjectAt(target_x, target_y-i)) {
			return;
		}
	}
	converDirectionAndDistanceToXY(down, dist, target_x, target_y);
	moveTo(target_x, target_y);
}

void Actor::sufferDamageIfDamageable() {

}
/*Obstacle class*/
Obstacle::Obstacle(const int ID, StudentWorld* sw, int x, int y)
	:Actor(ID, sw, x, y, 0, 2, 1.0,true)
{

}



/*Block class*/

Block::Block(StudentWorld* sw, int x, int y)
	:Obstacle(IID_BLOCK,sw,x,y),powerup(POWERUP_NONE),powerup_released(false)
{

}


Block::Block(StudentWorld* sw, int x, int y,int powerup)
	: Obstacle(IID_BLOCK, sw, x, y), powerup(powerup), powerup_released(false)
{
}


/*Pipe class*/

Pipe::Pipe(StudentWorld* sw, int x, int y)
	: Obstacle(IID_PIPE, sw, x, y)
{
}



/*Peach class*/

Peach::Peach(StudentWorld* sw, int x, int y)
	: Actor(IID_PEACH, sw, x, y),hp(1),invincibility_ticks(0),has_flower(false),has_mushroom(false),remaining_jump_distance(0),recharge_before_next_fire(0)
{
}
 void Peach::getBonked(bool bonkerIsInvinciblePeach) {
	 if (isInvincible()) {
		 return;
	 }
	 hp--;
	 invincibility_ticks = 10;
	 if (has_flower)
		 has_flower = false;
	 if (has_mushroom)
		 has_mushroom = false;
	 if (hp >= 1) {
		 getWorld()->playSound(SOUND_PLAYER_HURT);
	 }
	 else {
		 setDead();

	 }
}
void Peach::doSomethingAux()
{
	int target_x = 0;
	int target_y = 0;
	//step 1
	//if (!isAlive()) {
	//	return;
	//}
	//step 2
	//step 3
	if (invincibility_ticks>0) {
		invincibility_ticks--;
	}
	//step 4
	if (recharge_before_next_fire > 0) {
		recharge_before_next_fire--;
	}
	//step 5
	getWorld()->bonkObjectAt(getX(), getY(),isInvincible());
	//step 6
	if (remaining_jump_distance > 0) {
		converDirectionAndDistanceToXY(up, 4, target_x, target_y);
		if (getWorld()->isBlockingObjectAt(target_x, target_y)) {
			getWorld()->bonkObjectAt(target_x, target_y,isInvincible());
			remaining_jump_distance = 0;
		}
		else {
			moveTo(target_x, target_y);
			remaining_jump_distance--;
		}
	}
	else {
		//step 7
		fallIfPossible(4);
	}
	//Step 8
	int special_x = 0;
	int special_y = 0;
	int key;
	if (getWorld()->getKey(key))
	{
		//step 9
		switch (key)
		{
			
		case KEY_PRESS_LEFT:
			setDirection(left);
			converDirectionAndDistanceToXY(left, 4, special_x, special_y);
			if (getWorld()->isBlockingObjectAt(special_x, special_y)) {
				getWorld()->bonkObjectAt(special_x, special_y, isInvincible());

			}
			else{
				moveTo(special_x, special_y);
			}
			break;
		case KEY_PRESS_RIGHT:
			setDirection(0);
			converDirectionAndDistanceToXY(right, 4, special_x, special_y);
			if (getWorld()->isBlockingObjectAt(special_x , special_y)) {
				getWorld()->bonkObjectAt(special_x, special_y, isInvincible());
			}
			else{
				moveTo(special_x, special_y);
			}
			break;
		case KEY_PRESS_UP:
			if (getWorld()->isBlockingObjectAt(getX(), getY() - 4)) {
				if (has_mushroom)
					remaining_jump_distance = 12;
				else
					remaining_jump_distance = 8;
				getWorld()->playSound(SOUND_PLAYER_JUMP);
			}
			break;
		case KEY_PRESS_SPACE:
			if (has_flower&&(recharge_before_next_fire<=0)) {
				getWorld()->playSound(SOUND_PLAYER_FIRE);
				recharge_before_next_fire = 8;
				cerr << "shoot fireball" << endl; 
				//create fireball
			}
			break;
		}


	}
}

void Peach::updatePower(int powerUp) {
	switch (powerUp) {
	case POWERUP_FLOWER:
		has_flower = true;
		break;
	case POWERUP_MUSHROOM:
		has_mushroom = true;
		break;
	case POWERUP_STAR:
		invincibility_ticks = 10;
	}
}

//powerup class
Goodie::Goodie(StudentWorld* sw, int x, int y, int ID,int points)
	: Actor(ID, sw, x, y, 0, 1, 1.0), point_value(points)
{
}

void Goodie::doSomethingAux() {
	getWorld()->updateScore(point_value); 
	getWorld()->getPeach()->updatePower(POWERUP_FLOWER);
	getWorld()->getPeach()->updateHP(2);
	setDead();
	getWorld()->playSound(SOUND_PLAYER_POWERUP);
	return;


}
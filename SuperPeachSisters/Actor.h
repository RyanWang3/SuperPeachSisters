#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include <cstdlib>
const int POWERUP_NONE = 0;
const int POWERUP_STAR = 1;
const int POWERUP_FLOWER = 2;
const int POWERUP_MUSHROOM = 3;

class Actor : public GraphObject {
public:
	Actor(const int ID, StudentWorld* sw, int x, int y, int dir = 0, int depth = 0, double size = 1.0);
	virtual ~Actor(); 
	// Action to perform for each tick.
	void doSomething()
	{
		if (m_alive)
			doSomethingAux();
	}

	// Bonk this actor.  Parameter says whether bonker is Peach with invincibiity.
	virtual void getBonked(bool bonkerIsInvinciblePeach)
	{}


	// Fall the indicated distance if not blocked.
	void fallIfPossible(int dist);

	// Reverse the direction this actor is facing.
	void reverseDirection();

	StudentWorld* getWorld() { return m_world; }
	bool isAlive() { return m_alive; }
	void setDead() { m_alive = false; }

	// Does this actor block movement?
	virtual bool blocksMovement() const { return false; }
	// Is this actor an enemy?
	virtual bool isEnemy() const { return false; }
	// Set destx and desty to the coordinates dist pixels away in direction
// dir from this actor's position.
	void converDirectionAndDistanceToXY(int dir, int dist, int& destx, int& desty) const;
	bool tryToMove(int dir, int dist);
private:
	virtual void doSomethingAux() = 0;
	StudentWorld* m_world;
	bool m_alive; 
	
};

/*Goodie Class*/
class Goodie : public Actor {
public:
	Goodie(StudentWorld* sw, int x, int y, int ID);
private:
	virtual void doSomethingAux();
	virtual void getBonkedAux() = 0;
};

/*Flower Class*/
class Flower : public Goodie
{
public:
	Flower(StudentWorld* w, int x, int y);
private:
	virtual void getBonkedAux();
};
/*Mushroom Class*/
class Mushroom : public Goodie
{
public:
	Mushroom(StudentWorld* w, int x, int y);
private:
	virtual void getBonkedAux();
};

/*Star Class*/
class Star : public Goodie
{
public:
	Star(StudentWorld* w, int x, int y);
private:
	virtual void getBonkedAux();
};

/*Obstacle Class*/
class Obstacle : public Actor {
public:
	virtual bool blocksMovement() const { return true; }
	Obstacle(const int ID, StudentWorld* sw, int x, int y);
private:
	virtual void doSomethingAux(){}
};

/*Block Class*/
class Block : public Obstacle
{
public:
	Block(StudentWorld* sw, int x, int y, int power=POWERUP_NONE);
	virtual void getBonked(bool bonkerIsInvinciblePeach);
private:
	int powerup;
	bool powerup_released;
};
/*Pipe Class*/
class Pipe : public Obstacle
{
public:
	Pipe(StudentWorld* sw, int x, int y);
};

/*Peach Class*/
class Peach : public Actor
{
public:
	Peach(StudentWorld* sw, int x, int y);
	virtual void getBonked(bool bonkerIsInvinciblePeach);

	void updatePower(int powerUp);
	void updateHP(int hitpts) { hp = hitpts; }
	// Grant Peach invincibility for this number of ticks.
	bool isInvincible() const { return (invincibility_ticks>0); }
	bool hasShootPower() const { return has_flower; }
	bool hasJumpPower() const { return has_mushroom; }
	bool hasStarPower() const { return has_star; }


private:
	virtual void doSomethingAux();
	int hp;
	int invincibility_ticks;
	bool has_flower;
	bool has_mushroom;
	bool has_star;
	int remaining_jump_distance;
	int recharge_before_next_fire; 


};
/*Projectile Class*/
class Projectile : public Actor
{
public:
	Projectile(StudentWorld* w, int imageID, int x, int y, int dir);
private:
	virtual void doSomethingAux();
};

/*PiranhaFireball class*/
class PiranhaFireball : public Projectile
{
public:
	PiranhaFireball(StudentWorld* w, int x, int y, int dir);
private:
	virtual void doSomethingAux();

};


class PeachFireball : public Projectile
{
public:
	PeachFireball(StudentWorld* w, int x, int y, int dir);


};
/*Shell class*/
class Shell : public Projectile
{
public:
	Shell(StudentWorld* w, int x, int y, int dir);
};
/*Enemy class*/
class Enemy : public Actor
{
public:
	Enemy(StudentWorld* w, int imageID, int x, int y);
	virtual void getBonked(bool bonkerIsInvinciblePeach);
	virtual bool isEnemy() const { return true; }
private:
	virtual void doSomethingAux();
	virtual void getBonkedAux(){}

};


/*Goomba class*/
class Goomba : public Enemy
{
public:
	Goomba(StudentWorld* w, int x, int y);
private:
};
/*Koopa class*/

class Koopa : public Enemy
{
public:
	Koopa(StudentWorld* w, int x, int y);
private:
	virtual void getBonkedAux();

};
/*Piranha class*/

class Piranha : public Enemy
{
public:
	Piranha(StudentWorld* w, int x, int y);
private:
	virtual void doSomethingAux();
	int firing_delay;
};

class LevelEnder : public Actor
{
public:
	LevelEnder(StudentWorld* w, int x, int y, bool isGameEnder);
private:
	virtual void doSomethingAux();
	bool GameEnder;
};

#endif // ACTOR_H_

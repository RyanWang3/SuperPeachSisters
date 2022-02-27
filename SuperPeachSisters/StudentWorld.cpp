#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath),score(0)
{
}

int StudentWorld::init()
{
    Level lev(assetPath());
    string level_file = "level01.txt";
    Level::LoadResult result = lev.loadLevel(level_file);
    Level::GridEntry ge;
    //block = new Block(this, VIEW_WIDTH / 2, VIEW_HEIGHT / 2);
    for (int r = 0; r < GRID_HEIGHT; r++) {
        for (int c = 0; c < GRID_WIDTH; c++) {
            ge = lev.getContentsOf(r, c); // x=5, y=10
            switch (ge)
            {
            //case Level::empty:
            //    cout << "Location 5,10 is empty" << endl;
            //    break;
            //case Level::koopa:
            //    cout << "Location 5,10 starts with a koopa" << endl;
            //    break;
            //case Level::goomba:
            //    cout << "Location 5,10 starts with a goomba" << endl;
            //    break;
            case Level::peach:
                peach=new Peach(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH);
                break;
            case Level::flag:
                m_actors.push_back(new Flower(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH));
                break;
            case Level::block:
                m_actors.push_back(new Block(this, r* SPRITE_HEIGHT, c* SPRITE_WIDTH));
                break;
            case Level::star_goodie_block:
                m_actors.push_back(new Block(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH,POWERUP_STAR));
                break;
            case Level::flower_goodie_block:
                m_actors.push_back(new Block(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH, POWERUP_FLOWER));
                break;
            case Level::mushroom_goodie_block:
                m_actors.push_back(new Block(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH,POWERUP_MUSHROOM));
                break;
            case Level::pipe:
                m_actors.push_back(new Pipe(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH));
                break;
            //case Level::star_goodie_block:
            //    cout << "Location 5,10 has a star goodie block" << endl;
            //    break;
                // etc�
            }
        }
    }
    //someFunc();
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //block->doSomething(); 
   
    for (vector<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); ) {
        
        (*it)->doSomething(); 
        if ((*it)->isAlive() == false) {
            delete* it;
            it = m_actors.erase(it);
        }
        else {
            it++; 
        }
    }
    peach->doSomething(); 
    return GWSTATUS_CONTINUE_GAME;
    //decLives();
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator it = m_actors.begin(); 
    for (; it != m_actors.end();) {
        delete* it; 
        it = m_actors.erase(it);
    }
    delete peach; 
}
StudentWorld::~StudentWorld() {
    cleanUp(); 
}
bool StudentWorld::isBlockingObjectAt(int x, int y) {
    
    for (vector<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); it++) {
        if ((*it)->blocksMovement() && (*it)->getX() < (x + SPRITE_WIDTH) && (*it)->getX()+ (SPRITE_WIDTH) > x  && (*it)->getY() < y+SPRITE_HEIGHT && (*it)->getY() + (SPRITE_HEIGHT) > y) {
            return true;
        }
    }
    return false; 
}

bool StudentWorld::bonkObjectAt(int x, int y,bool isPeachInvincible) {
    bool flag = false;
    for (vector<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); it++) {
        if ((*it)->getX() < (x + SPRITE_WIDTH) && (*it)->getX() + (SPRITE_WIDTH) > x && (*it)->getY() < y + SPRITE_HEIGHT && (*it)->getY() + (SPRITE_HEIGHT) > y) {
            (*it)->getBonked(isPeachInvincible);
            flag= true;
        }
    }
    return flag;
}

void StudentWorld::updateScore(int x) {
    score += x; 
}

Peach* StudentWorld::getPeach() {
     return (Peach*)peach; 
}

bool StudentWorld::overlapsPeach(int x,int y) {
    if (peach->getX() < (x + SPRITE_WIDTH) && peach->getX() + (SPRITE_WIDTH) > x && peach->getY() < y + SPRITE_HEIGHT && peach->getY() + (SPRITE_HEIGHT) > y) {
        return true;
    }
    return false; 

}

bool StudentWorld::overlapsEnemy(int x, int y) {
    for (vector<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); it++) {
        if ((*it)->isEnemy() && (*it)->getX() < (x + SPRITE_WIDTH) && (*it)->getX() + (SPRITE_WIDTH) > x && (*it)->getY() < y + SPRITE_HEIGHT && (*it)->getY() + (SPRITE_HEIGHT) > y) {
            return true;
        }
    }
    return false;
}
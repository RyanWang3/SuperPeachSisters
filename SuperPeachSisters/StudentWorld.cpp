#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath),status(GWSTATUS_CONTINUE_GAME)
{
}

int StudentWorld::init()
{
    ostringstream oss;
    oss << "level0";
    oss << getLevel();
    oss << ".txt";

    Level lev(assetPath());
    string level_file = oss.str();
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_LEVEL_ERROR;
    else if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;

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
            case Level::koopa:
                m_actors.push_back(new Koopa(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH));
                break;
            case Level::goomba:
                m_actors.push_back(new Goomba(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH));
                break;
            case Level::peach:
                //m_actors.push_back(new PeachFireball(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH,180));

                peach = new Peach(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH);
                break;
            case Level::flag:
                m_actors.push_back(new LevelEnder(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH, false));
                break;
            case Level::block:
                m_actors.push_back(new Block(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH));
                break;
            case Level::star_goodie_block:
                m_actors.push_back(new Block(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH, POWERUP_STAR));
                break;
            case Level::flower_goodie_block:
                m_actors.push_back(new Block(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH, POWERUP_FLOWER));
                break;
            case Level::mushroom_goodie_block:
                m_actors.push_back(new Block(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH, POWERUP_MUSHROOM));
                break;
            case Level::pipe:
                m_actors.push_back(new Pipe(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH));
                break;
            case Level::piranha:
                m_actors.push_back(new Piranha(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH));
                break;
            case Level::mario:
                m_actors.push_back(new LevelEnder(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH, true));
                break;
                // etc…
            }
        }
    
    }
    //someFunc();
    status = GWSTATUS_CONTINUE_GAME;
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //block->doSomething(); 
    peach->doSomething();
    if (!peach->isAlive()) {
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    for (vector<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); ) {

        if (!(*it)->isAlive()) {
            delete* it;
            it = m_actors.erase(it);
        }
        else {
            (*it)->doSomething();
            it++; 
        }

    }
    if (status == GWSTATUS_FINISHED_LEVEL) {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    if (status == GWSTATUS_PLAYER_WON) {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    ostringstream oss;
    oss << "Lives: ";
    oss << getLives();
    oss << "  Level: ";
    oss.fill('0');
    oss << setw(2) << getLevel();
    oss << "  Points: ";
    oss.fill('0');
    oss << setw(5)<<getScore();
    if (getPeach()->hasStarPower()) {
        oss << " StarPower!";
    }
    if (getPeach()->hasShootPower()) {
        oss << " ShootPower!";
    }
    if (getPeach()->hasJumpPower()) {
        oss << " JumpPower!";
    }
    setGameStatText(oss.str());
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
void StudentWorld::endLevel(bool isGameWon) {
    if (isGameWon) {
        status = GWSTATUS_PLAYER_WON;
    }
    else {
        status = GWSTATUS_FINISHED_LEVEL;
    }
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
        if ((*it)->isEnemy() &&(*it)->isAlive()&& (*it)->getX() < (x + SPRITE_WIDTH) && (*it)->getX() + (SPRITE_WIDTH) > x && (*it)->getY() < y + SPRITE_HEIGHT && (*it)->getY() + (SPRITE_HEIGHT) > y) {
            return true;
        }
    }
    return false;
}

void StudentWorld::addActor(Actor* a) {
    m_actors.push_back(a);
}
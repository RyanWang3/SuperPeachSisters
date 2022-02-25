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
: GameWorld(assetPath)
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
            //case Level::flag:
            //    cout << "Location 5,10 is where a flag is" << endl;
            //    break;
            case Level::block:
                m_actors.push_back(new Block(this, r* SPRITE_HEIGHT, c* SPRITE_WIDTH));
                break;
            case Level::pipe:
                m_actors.push_back(new Pipe(this, r * SPRITE_HEIGHT, c * SPRITE_WIDTH));
                break;
            //case Level::star_goodie_block:
            //    cout << "Location 5,10 has a star goodie block" << endl;
            //    break;
                // etc…
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
   
    for (vector<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); it++) {
        (*it)->doSomething(); 
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
        if ((*it)->getX() - (SPRITE_WIDTH / 2) <= x && (*it)->getX()+ (SPRITE_WIDTH / 2) >= x  && (*it)->getY() - (SPRITE_HEIGHT / 2) <= y && (*it)->getY() + (SPRITE_HEIGHT / 2) >= y) {
            return true;
        }
    }
    return false; 
}

#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Missile.h"

//MissileMgr class to represent all missiles onscreen.
// anything that is useful to apply to the entire group i.e.
// spawning them, moving them, and checking for collisions with aliens or bombs
class MissileMgr
{
private:
	Texture missileTexture;						//Var for the texture all missiles will use
	list<Missile> missileList;					//List of missiles
	list<Missile>::iterator missileListItr;		//Iterator used for moving through the missile list
public:
	//constructor for the missileMgr.  calls loadTexture
	MissileMgr()
	{
		loadTexture();
	}
	//func to load missile texture from the file into the texture var in private data
	void loadTexture()
	{
		if (!missileTexture.loadFromFile("missile.png"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	//func to draw each individual missile in the list
	void drawMissiles(RenderWindow& win)
	{
		for (missileListItr = missileList.begin(); missileListItr != missileList.end(); missileListItr++)
		{
			missileListItr->draw(win);
		}
	}
	//func to create a new missile.
	void newMissile(Vector2f pos)
	{
		missileList.push_back(Missile(pos, missileTexture));
	}
	//func to move each individual missile in the list.  calls the missile class's move func
	void moveMissiles()
	{
		for (missileListItr = missileList.begin(); missileListItr != missileList.end();)
		{
			missileListItr->moveMissile();
			if (missileListItr->getYPos() < 0)
			{
				missileListItr = missileList.erase(missileListItr);
			}
			else
				missileListItr++;
		}
	}
	//returns an individual missile so the hitbox can be called.  Used in the loop that checks for
	// collisions in gameMgr
	Missile getMissile(int index)
	{
		missileListItr = missileList.begin();
		advance(missileListItr, index);
		return *missileListItr;
	}
	//getter for missile list's size
	int getListSize()
	{
		return missileList.size();
	}
	//func to delete an individual missile out of the list
	void deleteMissile(int index)
	{
		missileListItr = missileList.begin();
		advance(missileListItr, index);
		missileList.erase(missileListItr);
	}
	//func to delete all of the missiles out of the list
	void deleteAllMissiles()
	{
		missileList.clear();
	}
};
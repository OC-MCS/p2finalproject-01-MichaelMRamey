#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <list>
#include "alien.h"
#include "BombMgr.h"

//AlienMgr class to represent the alien horde as a whole.
// anything that is useful to apply to the entire group i.e.
// spawning them, moving them, and checking for collisions with missiles
class AlienMgr
{
private:
	Texture alienTexture;				//Var for the texture all aliens will use
	list<Alien> alienList;				//List of aliens
	list<Alien>::iterator alienListItr;	//Iterator used for moving though the alien list
	int aliensKilled;					//Counter for number of aliens killed
public:
	//Constructor for AlienMgr.  Simply loads the texture.
	AlienMgr()
	{
		loadTexture();
	}
	//Function to load texture for the alien horde
	void loadTexture()
	{
		if (!alienTexture.loadFromFile("alien1.png"))
		{
			cout << "Unable to load alien texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	//Function to draw each individual alien.  Called from main's "drawing loop"
	void drawAliens(RenderWindow& win)
	{
		for (alienListItr = alienList.begin(); alienListItr != alienList.end(); alienListItr++)
		{
			alienListItr->draw(win);
		}
	}
	//Function for adding a new alien to the AlienList.  Needs a position for the alien to spawn at.
	void newAlien(Vector2f pos)
	{
		alienList.push_back(Alien(pos, alienTexture));
	}
	//Function to spawn a line of 10 aliens
	void spawnAliens()
	{
		float x = 40;	//Var for the alien's spawning x position
		for (int i = 0; i < 10; i++)
		{
			newAlien(Vector2f(x, 100));
			x += 75;
		}
	}
	//Function to move each alien.  Calls individual alien's move func
	void moveAliens()
	{
		for (alienListItr = alienList.begin(); alienListItr != alienList.end(); alienListItr++)
		{
			alienListItr->moveAlien();
		}
	}
	//Function to delete all of the aliens from the list
	void deleteAllAliens()
	{
		alienList.clear();
	}
	//Function to determine if the alien horde has reached the player's y position
	bool aliensReachedPlayer()
	{
		bool result = false;  //Bool that stores whether or not the aliens have reached the player
		for (alienListItr = alienList.begin(); alienListItr != alienList.end(); alienListItr++)
		{
			if (alienListItr->getYPos() > 550)
			{
				result = true;
			}
			else
				result = false;
		}
		return result;
	}
	//Function to check each individual alien for a missile collision using the hitbox functions.
	//Checks every combination of alien with the missile hitbox that is passed.
	bool checkForHit(FloatRect missileHitbox)
	{
		bool hitAlien = false;  //Bool to store whether an alien has been hit
		for (alienListItr = alienList.begin(); alienListItr != alienList.end();)
		{
			if (alienListItr->getHitbox().intersects(missileHitbox))
			{
				alienListItr = alienList.erase(alienListItr);
				aliensKilled++;
				hitAlien = true;
			}
			else
				alienListItr++;
		}
		return hitAlien;
	}
	//Func to get the number of aliens killed during the game
	int getAliensKilled()
	{
		return aliensKilled;
	}
	//Func to reset the number of aliens killed
	void resetKills()
	{
		aliensKilled = 0;
	}
	//Func to check if all of the aliens are dead
	bool allAliensDead()
	{
		bool result = false;	//Bool to store whether all the aliens are dead
		if (alienList.size() == 0)
		{
			result = true;
			if (!alienTexture.loadFromFile("alien2.png"))
			{
				cout << "Unable to load alien texture!" << endl;
				exit(EXIT_FAILURE);
			}
		}
		return result;
	}
	//Func to choose a random alien to launch a bomb
	//This func might be particularly inefficient because
	//it breaks some encapsulation between AlienMgr and BombMgr.
	void randomBomb(BombMgr& bombMgr)
	{
		//Generate a random number to select the alien that will drop a bomb
		int randomNumber = rand() % alienList.size();
		alienListItr = alienList.begin();
		advance(alienListItr, randomNumber);
		bombMgr.newBomb(alienListItr->getPosition());
	}
};
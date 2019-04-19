#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include "Bomb.h"

//BombMgr class to represent all bombs on the screen.
// anything that is useful to apply to the entire group i.e.
// spawning them, moving them, and checking for collisions with missiles or the player char
class BombMgr
{
private:
	Texture bombTexture;				//Var for the texture all bombs will use
	list<Bomb> bombList;				//List of Bombs
	list<Bomb>::iterator bombListItr;	//Iterator used for moving through the bomb list
	int bombSpawnRate = 200;			//Spawn rate for bombs.  Lower number means more bombs
public:
	//Constructor for the bombMgr.  Calls loadTexture.
	BombMgr()
	{
		loadTexture();
	}
	//Loads bombTexture and stores in private data
	void loadTexture()
	{
		if (!bombTexture.loadFromFile("Bomb.jpg"))
		{
			cout << "Unable to load missile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	//Func to draw each individual bomb.  Called from main's "drawing loop"
	void drawBombs(RenderWindow& win)
	{
		for (bombListItr = bombList.begin(); bombListItr != bombList.end(); bombListItr++)
		{
			bombListItr->draw(win);
		}
	}
	//Func for adding a new bomb to the list
	void newBomb(Vector2f pos)
	{
		bombList.push_back(Bomb(pos, bombTexture));
	}
	//Func to move each bomb.  Calls individual bomb's move func
	void moveBombs()
	{
		for (bombListItr = bombList.begin(); bombListItr != bombList.end();)
		{
			bombListItr->moveBomb();
			if (bombListItr->getYPos() < 0)
			{
				bombListItr = bombList.erase(bombListItr);
			}
			else
				bombListItr++;
		}
	}
	//Func that returns the size of the alienList
	int getListSize()
	{
		return bombList.size();
	}
	//Func to delete all bombs from the list
	void deleteAllBombs()
	{
		bombList.clear();
	}
	//func that returns a bool and handles interaction between a bomb instance and a missile
	// this function finds any collisions and deletes the bomb that has been hit.  returns a
	// bool that causes the corresponding missile to be deleted as well (in gameMgr)
	bool checkForMissileHit(FloatRect missileHitbox)
	{
		bool hitBomb = false;	//Bool to be returned. Stores if a bomb has been hit
		for (bombListItr = bombList.begin(); bombListItr != bombList.end();)
		{
			if (bombListItr->getHitbox().intersects(missileHitbox))
			{
				bombListItr = bombList.erase(bombListItr);
				hitBomb = true;
			}
			else
				bombListItr++;
		}
		return hitBomb;
	}
	//Func that handles bomb/ship interaction.  Returns true if ship has been hit
	bool checkForShipHit(FloatRect shipHitbox)
	{
		bool hitPlayer = false;
		for (bombListItr = bombList.begin(); bombListItr != bombList.end();)
		{
			if (bombListItr->getHitbox().intersects(shipHitbox))
			{
				bombListItr = bombList.erase(bombListItr);
				hitPlayer = true;
			}
			else
				bombListItr++;
		}
		return hitPlayer;
	}
	//Func to get the bomb spawn rate
	int getBombSpawnRate()
	{
		return bombSpawnRate;
	}
};

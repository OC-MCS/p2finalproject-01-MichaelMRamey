#pragma once
#include "AlienMgr.h"
#include "MissileMgr.h"

//GameManager class to integrate all the other managers together
//Handles game start, player lives, levels, and calls to collision functions in group mgrs
class GameMgr
{
private:
	int playerLivesLeft, levelNum, bombCounter;  //PlayerLivesLeft: stores how many lives player has
	//LevelNum: stores what level the player is on.  bombCounter: incremented every time gameStatus is
	// checked.  When it reaches a certain number a bomb will be launched (call alienMgr.randomBomb())
	bool inGame, playerWin;	//Bool vars to check if player is still in game or if they have won.
public:
	//Func for whenever the game starts.  Does initialization for important game statistics and resets missile, alien, and bomb lists
	void startGame(AlienMgr& alienMgr, MissileMgr& missileMgr, BombMgr& bombMgr, Ship& ship)
	{
		playerLivesLeft = 3;
		levelNum = 1;
		bombCounter = 0;
		inGame = true;
		playerWin = false;
		alienMgr.deleteAllAliens();
		alienMgr.spawnAliens();
		alienMgr.loadTexture();
		alienMgr.resetKills();

		missileMgr.deleteAllMissiles();

		bombMgr.deleteAllBombs();

		ship.resetPos();
	}

	//Func to check game status:
	// Do this every frame to check for collisions and level change
	// This function checks for collisions between: missiles and aliens, missiles and bombs, bombs and the ship
	// Also checks if aliens have reached the ship's y position
	void checkGameStatus(AlienMgr& alienMgr, MissileMgr& missileMgr, BombMgr& bombMgr, Ship& ship)
	{
		//Check if aliens have reached the bottom
		if (alienMgr.aliensReachedPlayer())
		{
			loseALife(alienMgr);
		}
		
		//Check for and handle missiles hitting bombs
		for (int i = 0; i < missileMgr.getListSize(); i++)
		{
			if (bombMgr.checkForMissileHit(missileMgr.getMissile(i).getHitbox()))
			{
				missileMgr.deleteMissile(i);
			}
		}

		//Check for and handle missiles hitting aliens
		for (int i = 0; i < missileMgr.getListSize(); i++)
		{
			if (alienMgr.checkForHit(missileMgr.getMissile(i).getHitbox()))
			{
				missileMgr.deleteMissile(i);
				if (alienMgr.allAliensDead())
				{
					levelNum++;
					alienMgr.deleteAllAliens();
					missileMgr.deleteAllMissiles();
					bombMgr.deleteAllBombs();
					alienMgr.spawnAliens();
					if (levelNum == 3)
					{
						playerWin = true;
						inGame = false;
					}
				}
			}	
		}

		//check for and handle bombs hitting the ship
		for (int i = 0; i < bombMgr.getListSize(); i++)
		{
			if (bombMgr.checkForShipHit(ship.getHitbox()))
			{
				loseALife(alienMgr);
				bombMgr.deleteAllBombs();
				missileMgr.deleteAllMissiles();
			}
		}

		//check if enough frames have gone by to spawn a bomb and do so if needed
		if (bombCounter == bombMgr.getBombSpawnRate())
		{
			for (int i = 0; i < levelNum; i++)
			{
				alienMgr.randomBomb(bombMgr);
				bombCounter = 0;
			}
		}
		bombCounter++;
	}

	//func for when the player loses a life.  Also resets the current level
	void loseALife(AlienMgr& alienMgr)
	{
		playerLivesLeft--;
		alienMgr.deleteAllAliens();
		alienMgr.spawnAliens();
		if (playerLivesLeft == 0)
		{
			playerWin = false;
			inGame = false;
		}
	}

	//getter for playerlivesleft
	int livesLeft()
	{
		return playerLivesLeft;
	}

	//getter for levelNum
	int getLevelNum()
	{
		return levelNum;
	}

	//getter for inGame
	bool getInGame()
	{
		return inGame;
	}

	//getter for playerWin
	bool getPlayerWin()
	{
		return playerWin;
	}
};
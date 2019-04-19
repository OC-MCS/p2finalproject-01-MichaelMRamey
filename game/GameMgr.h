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
	//Func for whenever the game starts
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

	// Do this every frame to check for collisions and level change
	void checkGameStatus(AlienMgr& alienMgr, MissileMgr& missileMgr, BombMgr& bombMgr, Ship& ship)
	{
		if (alienMgr.aliensReachedPlayer())
		{
			loseALife(alienMgr);
		}
		
		for (int i = 0; i < missileMgr.getListSize(); i++)
		{
			if (bombMgr.checkForMissileHit(missileMgr.getMissile(i).getHitbox()))
			{
				missileMgr.deleteMissile(i);
			}
		}
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
		for (int i = 0; i < bombMgr.getListSize(); i++)
		{
			if (bombMgr.checkForShipHit(ship.getHitbox()))
			{
				loseALife(alienMgr);
			}
		}
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
	int livesLeft()
	{
		return playerLivesLeft;
	}
	int getLevelNum()
	{
		return levelNum;
	}
	bool getInGame()
	{
		return inGame;
	}
	bool getPlayerWin()
	{
		return playerWin;
	}
};
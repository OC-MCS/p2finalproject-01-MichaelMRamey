#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf; 
#include <list>
#include "Ship.h"
#include "GameMgr.h"
#include "MissileMgr.h"
#include "AlienMgr.h"
#include "BombMgr.h"
#include "Game_UI.h"
#include "Menu_UI.h"
#include "BombMgr.h"
//============================================================
// Michael Ramey
// Programming 2: Final project (Space Invaders!)
// Due: April 19th
//============================================================

int main()
{
	const int WINDOW_WIDTH = 800;	//window width var
	const int WINDOW_HEIGHT = 600;	//window height var

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Interstellar Attackers!");
	window.setFramerateLimit(60); //Set how how many frames can happen per second

	Vector2f shipStartPosition(400, 550);	//Set ship start position
	Ship ship(shipStartPosition);			//Create an instance of a ship

	GameMgr gameMgr;			//Create an instance of a GameMgr
	Menu_UI menuUI;				//Create an instance of a Menu_UI
	Game_UI gameUI(window);		//Create an instance of a Game_UI
	MissileMgr missileMgr;		//Create an instance of a MissileMgr
	AlienMgr alienMgr;			//Create an instance of an AlienMgr
	BombMgr bombMgr;			//Create an instance of a BombMgr

	bool inGame = false;		//Declare and set a bool var to determine if player is in game
	bool gamePlayed = false;	//Declare and set a bool var to determine if the animation loop has run yet

	//Set up background====================================
	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}

	Sprite background;
	background.setTexture(starsTexture);
	background.setScale(1.5, 1.5);
	//=====================================================

	//Check for user interaction in this loop
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::MouseButtonReleased && !inGame)
			{
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				inGame = menuUI.handleMouseUp(mousePos);
				if (inGame) {
					gameMgr.startGame(alienMgr, missileMgr, bombMgr, ship);
				}
			}
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					missileMgr.newMissile(ship.getPosition());
				}
			}
		}

		//========================
		//======DRAWING LOOP======
		//========================
		window.draw(background);


		//If statement for whether the player is in game
		if (!inGame)
		{
			menuUI.drawBtn(window);
			if (gameMgr.getPlayerWin() && gamePlayed)
			{
				menuUI.displayVictory(window);
			}
			else if (gamePlayed)
				menuUI.displayDefeat(window);
			else
				menuUI.displayTitle(window);
		}
		else
		{
			//ship functions
			ship.moveShip();
			ship.draw(window);
			
			//missileMgr functions
			missileMgr.moveMissiles();
			missileMgr.drawMissiles(window);

			//alienMgr functions
			alienMgr.moveAliens();
			alienMgr.drawAliens(window);

			//bombMgr functions
			bombMgr.moveBombs();
			bombMgr.drawBombs(window);

			//gameMgr functions
			gameMgr.checkGameStatus(alienMgr, missileMgr, bombMgr, ship);
			inGame = gameMgr.getInGame(); //Important!  determines if user is still in game

			//game UI functions
			gameUI.dispLives(window, gameMgr.livesLeft());
			gameUI.dispKills(window, alienMgr.getAliensKilled());
			gameUI.dispLevelNum(window, gameMgr.getLevelNum());
			
			gamePlayed = true; //set gamePlayed to true because we have now gone through 1 frame
		}
		window.display();

	} // end body of animation loop

	return 0;
}
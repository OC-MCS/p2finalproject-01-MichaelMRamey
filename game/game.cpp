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
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	Vector2f shipStartPosition(400, 550);
	Ship ship(shipStartPosition);

	GameMgr gameMgr;
	Menu_UI menuUI;
	Game_UI gameUI(window);
	MissileMgr missileMgr;
	AlienMgr alienMgr;
	BombMgr bombMgr;

	bool inGame = false;
	bool gamePlayed = false;

	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}

	Sprite background;
	background.setTexture(starsTexture);
	background.setScale(1.5, 1.5);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
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

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);

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
			//detect key presses to update the position of the ship. 
			//See moveShip() function above.
			ship.moveShip();

			// draw the ship on top of background 
			// (the ship from previous frame was erased when we drew background)
			ship.draw(window);
			
			missileMgr.moveMissiles();
			missileMgr.drawMissiles(window);

			alienMgr.moveAliens();
			alienMgr.drawAliens(window);

			bombMgr.moveBombs();
			bombMgr.drawBombs(window);

			gameMgr.checkGameStatus(alienMgr, missileMgr, bombMgr, ship);
			gameUI.dispLives(window, gameMgr.livesLeft());
			gameUI.dispKills(window, alienMgr.getAliensKilled());
			gameUI.dispLevelNum(window, gameMgr.getLevelNum());
			inGame = gameMgr.getInGame();
			gamePlayed = true;
			// end the current frame; this makes everything that we have
			// already "drawn" actually show up on the screen
			

			// At this point the frame we have built is now visible on screen.
			// Now control will go back to the top of the animation loop
			// to build the next frame. Since we begin by drawing the
			// background, each frame is rebuilt from scratch.
		}
		window.display();

	} // end body of animation loop

	return 0;
}
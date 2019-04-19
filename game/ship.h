#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//Ship Class to represent the player character: the green ship
class Ship
{
private:
	Sprite ship;				//Ship sprite var
	Texture shipTexture;		//var to store the ship's texture
	Vector2f startingPos;		//var to store the ship's starting position
	const float DISTANCE = 5.0f;//const var for how far the ship will move when a key is pressed
public:
	//constructor for a ship.  sets starting position and calls loadtexture
	Ship(Vector2f shipPos)
	{
		startingPos = shipPos;
		ship.setPosition(startingPos);
		loadTexture();
		ship.setTexture(shipTexture);
	}
	//func to load the shipTexture from the file and store it in the private data
	void loadTexture()
	{
		if (!shipTexture.loadFromFile("ship.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	//getter for the ship's vector2f position
	Vector2f getPosition()
	{
		return ship.getPosition();
	}
	//func to move the ship in the direction the key is pressed
	void moveShip()
	{
		if (Keyboard::isKeyPressed(Keyboard::Left) && ship.getPosition().x > 2)
		{
			ship.move(-DISTANCE, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && ship.getPosition().x < 780)
		{
			ship.move(DISTANCE, 0);
		}
	}
	//func to draw the ship. Used in main's "drawing loop"
	void draw(RenderWindow& win)
	{
		win.draw(ship);
	}
	//func to get the ship's floatRect "hitbox"
	FloatRect getHitbox()
	{
		return ship.getGlobalBounds();
	}
	//func to reset the ship's position to the middle
	void resetPos()
	{
		ship.setPosition(startingPos);
	}
};
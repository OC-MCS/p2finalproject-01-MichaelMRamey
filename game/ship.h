#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
class Ship
{
private:
	Sprite ship;
	Texture shipTexture;
	Vector2f startingPos;
public:
	Ship(Vector2f shipPos)
	{
		startingPos = shipPos;
		ship.setPosition(startingPos);
		loadTexture();
		ship.setTexture(shipTexture);
	}
	void loadTexture()
	{
		if (!shipTexture.loadFromFile("ship.png"))
		{
			cout << "Unable to load ship texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	void setPosition(Vector2f pos)
	{
		ship.setPosition(pos);
	}
	Vector2f getPosition()
	{
		return ship.getPosition();
	}
	void moveShip()
	{
		const float DISTANCE = 5.0f;

		if (Keyboard::isKeyPressed(Keyboard::Left) && ship.getPosition().x > 2)
		{
			ship.move(-DISTANCE, 0);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && ship.getPosition().x < 780)
		{
			ship.move(DISTANCE, 0);
		}
	}
	void draw(RenderWindow& win)
	{
		win.draw(ship);
	}
	FloatRect getHitbox()
	{
		return ship.getGlobalBounds();
	}
	void resetPos()
	{
		ship.setPosition(startingPos);
	}
};
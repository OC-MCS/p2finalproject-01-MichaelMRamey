#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
class Alien
{
private:
	Sprite alien;
	const float MOVE_DISTANCE = 0.5f;
public:
	Alien(Vector2f pos, Texture& texture)
	{
		alien.setPosition(pos);
		alien.setTexture(texture);
	}
	void draw(RenderWindow& win)
	{
		win.draw(alien);
	}
	void moveAlien()
	{
		alien.move(0, MOVE_DISTANCE);
	}
	float getYPos()
	{
		return alien.getPosition().y;
	}
	FloatRect getHitbox()
	{
		return alien.getGlobalBounds();
	}

};
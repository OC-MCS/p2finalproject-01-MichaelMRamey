#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
class Missile
{
private:
	Sprite missile;
	const float MOVE_DISTANCE = 5.0f;
public:
	Missile(Vector2f shipPos, Texture& texture)
	{
		missile.setPosition(shipPos);
		missile.setTexture(texture);
	}
	void moveMissile()
	{
		missile.move(0, -MOVE_DISTANCE);
	}
	void setPosition(Vector2f pos)
	{
		missile.setPosition(pos);
	}
	void draw(RenderWindow& win)
	{
		win.draw(missile);
	}
	Vector2f getPosition()
	{
		return missile.getPosition();
	}
};
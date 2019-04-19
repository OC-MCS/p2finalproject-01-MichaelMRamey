#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
class Bomb
{
private:
	Sprite bomb;
	const float MOVE_DISTANCE = 1.0f;
public:
	Bomb(Vector2f bombPos, Texture& texture)
	{
		bomb.setPosition(bombPos);
		bomb.setTexture(texture);
	}
	void moveBomb()
	{
		bomb.move(0, MOVE_DISTANCE);
	}
	void setPosition(Vector2f pos)
	{
		bomb.setPosition(pos);
	}
	void draw(RenderWindow& win)
	{
		win.draw(bomb);
	}
	Vector2f getPosition()
	{
		return bomb.getPosition();
	}
	FloatRect getHitbox()
	{
		return bomb.getGlobalBounds();
	}
	float getYPos()
	{
		return bomb.getPosition().y;
	}
};
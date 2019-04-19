#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//Missile Class to represent a single missile
class Missile
{
private:
	Sprite missile;						//Missile sprite var
	const float MOVE_DISTANCE = 5.0f;	//Const move speed for the missile
public:
	//Constructor for a missile. must have a vector2f position and texture
	Missile(Vector2f shipPos, Texture& texture)
	{
		missile.setPosition(shipPos);
		missile.setTexture(texture);
	}
	//func to move the missile by the MOVE_DISTANCE increment
	void moveMissile()
	{
		missile.move(0, -MOVE_DISTANCE);
	}
	//func to set the position for the missile.  Used when spawning in a new missile
	void setPosition(Vector2f pos)
	{
		missile.setPosition(pos);
	}
	//func to draw the missile.  Used in main's "drawing loop"
	void draw(RenderWindow& win)
	{
		win.draw(missile);
	}
	//func to get the missiles FloatRect "hitbox"
	FloatRect getHitbox()
	{
		return missile.getGlobalBounds();
	}
	//func to get the y position of the missile
	float getYPos()
	{
		return missile.getPosition().y;
	}
};
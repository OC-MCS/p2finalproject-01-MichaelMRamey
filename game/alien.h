#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//Alien Class to represent a single alien
class Alien
{
private:
	Sprite alien;						//Alien sprite
	const float MOVE_DISTANCE = 0.3f;	//Const move speed for the alien
public:
	//Constructor for an alien.  Must have a vector2f position and texture
	Alien(Vector2f pos, Texture& texture)
	{
		alien.setPosition(pos);
		alien.setTexture(texture);
	}
	//Draw function for an alien.  Draws this instance of alien to the render win
	void draw(RenderWindow& win)
	{
		win.draw(alien);
	}
	//Function for alien movement.  Uses move_distance from private data
	void moveAlien()
	{
		alien.move(0, MOVE_DISTANCE);
	}
	//Function to get the y position of the alien.  Used for finding
	// when aliens reach the player at the bottom of the screen.
	float getYPos()
	{
		return alien.getPosition().y;
	}
	//Function to get position of the alien.  Used for spawning bombs.
	Vector2f getPosition()
	{
		return alien.getPosition();
	}
	//Function to get the "hitbox" of the alien.  Used to check if a missile has impacted this alien.
	FloatRect getHitbox()
	{
		return alien.getGlobalBounds();
	}

};
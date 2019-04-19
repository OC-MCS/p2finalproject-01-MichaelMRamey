#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//Bomb class to represent an individual bomb
//(projectile launched by alien)
class Bomb
{
private:
	Sprite bomb;						//Sprite for the bomb
	const float MOVE_DISTANCE = 1.0f;	//const to determine how fast a bomb will move
public:
	//Constructor for a single bomb.  Needs a position to spawn at and a texture
	Bomb(Vector2f bombPos, Texture& texture)
	{
		bomb.setPosition(bombPos);
		bomb.setTexture(texture);
	}
	//Func to move the bomb by the set distance (happens every frame the bomb is onscreen)
	void moveBomb()
	{
		bomb.move(0, MOVE_DISTANCE);
	}
	//Func to set the position of a bomb.  Used when a bomb needs to be spawned at an alien's location
	void setPosition(Vector2f pos)
	{
		bomb.setPosition(pos);
	}
	//Func to draw the bomb.  Called in main's "Drawing loop"
	void draw(RenderWindow& win)
	{
		win.draw(bomb);
	}
	//Func to get the Vector2f pos of a bomb
	Vector2f getPosition()
	{
		return bomb.getPosition();
	}
	//Func to get the "hitbox" of a bomb (the rectangle area the sprite takes up)
	FloatRect getHitbox()
	{
		return bomb.getGlobalBounds();
	}
	//Func to get the y position of a bomb.  Useful to determine when a bomb goes
	// offscreen and should be deleted.
	float getYPos()
	{
		return bomb.getPosition().y;
	}
};
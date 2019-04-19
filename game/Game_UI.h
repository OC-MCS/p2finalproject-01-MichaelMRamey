#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <string>

//Game_UI class to represent the User interface for while the game is running
class Game_UI
{
private:
	Font font;	//Font for all of the text to be displayed
	Text lives, numLives, aliensKilled, numKilled, level, numLevel;	//Text vars for lives (and the number of lives left),
																	//kills/number of kills, level/which number level the player is on
public:
	//Constructor for the GameUI.  Sets the text font, color, size, and position for text vars in private data.
	Game_UI(RenderWindow& win) 
	{
		loadFont();

		lives.setString("Lives: ");
		lives.setFont(font);
		lives.setCharacterSize(50);
		lives.setFillColor(Color::White);
		lives.setPosition(25, 25);
		numLives.setCharacterSize(40);
		numLives.setFont(font);
		numLives.setFillColor(Color::White);
		numLives.setPosition(150, 30);

		aliensKilled.setString("Kills: ");
		aliensKilled.setFont(font);
		aliensKilled.setCharacterSize(50);
		aliensKilled.setFillColor(Color::White);
		aliensKilled.setPosition(300, 25);
		numKilled.setCharacterSize(40);
		numKilled.setFont(font);
		numKilled.setFillColor(Color::White);
		numKilled.setPosition(425, 30);

		level.setString("Level: ");
		level.setFont(font);
		level.setCharacterSize(50);
		level.setFillColor(Color::White);
		level.setPosition(600, 25);
		numLevel.setCharacterSize(40);
		numLevel.setFont(font);
		numLevel.setFillColor(Color::White);
		numLevel.setPosition(725, 30);
	}
	//Func to load the font
	void loadFont()
	{
		if (!font.loadFromFile("C:\\Windows\\Fonts\\ITCBLKAD.TTF"))
			die("couldn't load font");
	}
	//Func to draw text concerning player lives.  Used in main's "drawing loop"
	void dispLives(RenderWindow& win, int livesCount)
	{
		numLives.setString(to_string(livesCount));
		win.draw(lives);
		win.draw(numLives);
	}
	//Func to draw text concerning alien kills.  Used in main's "drawing loop"
	void dispKills(RenderWindow& win, int killCount)
	{
		numKilled.setString(to_string(killCount));
		win.draw(numKilled);
		win.draw(aliensKilled);
	}
	//Func to draw text concerning the level.  Used in main's "drawing loop"
	void dispLevelNum(RenderWindow& win, int lvlNum)
	{
		numLevel.setString(to_string(lvlNum));
		win.draw(numLevel);
		win.draw(level);
	}
	//Die func for font loading error.  Displays error msg and "dies gracefully"
	void die(string msg)
	{
		cout << msg << endl;
		exit(-1);
	}
};

#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <string>
class Game_UI
{
private:
	Font font;
	Text lives, numLives, aliensKilled, numKilled;
public:
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
	}
	void loadFont()
	{
		if (!font.loadFromFile("C:\\Windows\\Fonts\\ITCBLKAD.TTF"))
			die("couldn't load font");
	}
	void dispLives(RenderWindow& win, int livesCount)
	{
		numLives.setString(to_string(livesCount));
		win.draw(lives);
		win.draw(numLives);
	}
	void dispKills(RenderWindow& win, int killCount)
	{
		numKilled.setString(to_string(killCount));
		win.draw(numKilled);
		win.draw(aliensKilled);
	}
	void die(string msg)
	{
		cout << msg << endl;
		exit(-1);
	}
};

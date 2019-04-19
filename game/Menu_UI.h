#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Menu_UI
{
private:
	Font font;
	Text btnText, endgameText, titleText;
	RectangleShape startBtn;
public:
	Menu_UI()
	{
		loadFont();
		btnText.setString("START");
		btnText.setFont(font);
		btnText.setCharacterSize(50);
		btnText.setFillColor(Color::Black);
		btnText.setPosition(300, 260);

		startBtn.setPosition(Vector2f(300,250));
		startBtn.setSize(Vector2f(200, 100));
		startBtn.setOutlineThickness(2);
		startBtn.setOutlineColor(Color::Red);

		endgameText.setFont(font);
		endgameText.setCharacterSize(100);
		endgameText.setPosition(150, 100);

		endgameText.setFont(font);
		endgameText.setCharacterSize(100);
		endgameText.setPosition(150, 100);

		titleText.setString("-Interstellar attackers-");
		titleText.setFont(font);
		titleText.setCharacterSize(100);
		titleText.setFillColor(Color::White);
		titleText.setPosition(20, 100);
	}
	void displayVictory(RenderWindow& win)
	{
		endgameText.setString("YOU WIN!!!");
		endgameText.setFillColor(Color::Yellow);
		win.draw(endgameText);
	}
	void displayDefeat(RenderWindow& win)
	{
		endgameText.setString("YOU LOST...");
		endgameText.setFillColor(Color::Red);
		win.draw(endgameText);
	}
	void drawBtn(RenderWindow& win)
	{
		win.draw(startBtn);
		win.draw(btnText);
	}
	void displayTitle(RenderWindow& win)
	{
		win.draw(titleText);
	}
	bool handleMouseUp(Vector2f mouse)
	{
		return startBtn.getGlobalBounds().contains(mouse);
	}
	void loadFont()
	{
		if (!font.loadFromFile("C:\\Windows\\Fonts\\ITCBLKAD.TTF"))
			die("couldn't load font");
	}
	void die(string msg)
	{
		cout << msg << endl;
		exit(-1);
	}
};
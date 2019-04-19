#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

class Menu_UI
{
private:
	Font font;
	Text btnText;
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
	}
	void drawBtn(RenderWindow& win)
	{
		win.draw(startBtn);
		win.draw(btnText);
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
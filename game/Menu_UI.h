#pragma once
#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

//MenuUI class to represent User interface at start screen
class Menu_UI
{
private:
	Font font;								//Font var for text
	Text btnText, endgameText, titleText;	//Text vars for the start button, title, and results screen
	RectangleShape startBtn;				//Rectangle var for the start button
public:
	//Constructor for the MenuUI.  Sets the text font, color, size, and position for text vars and button in private data.
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
	//func to set gameover screen text and draw it.  Used in main's "drawing loop"
	void displayVictory(RenderWindow& win)
	{
		endgameText.setString("YOU WIN!!!");
		endgameText.setFillColor(Color::Yellow);
		win.draw(endgameText);
	}
	//func to set gameover screen text and draw it.  Used in main's "drawing loop"
	void displayDefeat(RenderWindow& win)
	{
		endgameText.setString("YOU LOST...");
		endgameText.setFillColor(Color::Red);
		win.draw(endgameText);
	}
	//func to draw the start button and it's text.  Used in main's "drawing loop"
	void drawBtn(RenderWindow& win)
	{
		win.draw(startBtn);
		win.draw(btnText);
	}
	//func to draw title screen text.  Used in main's "drawing loop"
	void displayTitle(RenderWindow& win)
	{
		win.draw(titleText);
	}
	//func to check if player has clicked on the start button
	bool handleMouseUp(Vector2f mouse)
	{
		return startBtn.getGlobalBounds().contains(mouse);
	}
	//func to load the font into "font" private data
	void loadFont()
	{
		if (!font.loadFromFile("C:\\Windows\\Fonts\\ITCBLKAD.TTF"))
			die("couldn't load font");
	}
	//Die func for font loading error.  Displays error msg and "dies gracefully"
	void die(string msg)
	{
		cout << msg << endl;
		exit(-1);
	}
};
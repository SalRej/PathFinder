#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Button
{
public:
	RectangleShape button;
	Font arial;
	Text text;
	Color color;
	//if i press a button wich is supoused to be as a choise the button gona stay pressed 
	//and im gona use it when i pres generate or find
	bool chosen;
	Button();
	void Draw(RenderWindow&);
	void SetPosition(float x, float y);
	void SetSize(float x, float y);
	bool IsButtonPressed(RenderWindow&);
};
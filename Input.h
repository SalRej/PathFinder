#pragma once
#include"Board.h"
#include"Slides Input.h"
#include"Board Input.h"
#include"Buttons Input.h"

inline void Board::Input(RenderWindow& window)
{
	//menu imput
	if (Mouse::isButtonPressed(Mouse::Left))
	{

		//sliders
		Slides_Input(window);
		//pathfinding
		Buttons_Input(window);
	}
	//board input
	Board_Input(window);
}
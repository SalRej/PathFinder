#pragma once
#include "Board.h"

inline void Board::Board_Input(RenderWindow&window)
{
	int x, y;
	if (Mouse::isButtonPressed(Mouse::Left) && Keyboard::isKeyPressed(Keyboard::Key::LControl))
	{
		x = Mouse::getPosition(window).x / size;
		y = Mouse::getPosition(window).y / size;
		if (x > 0 && x < boardSize - 1 && y>0 && y < boardSize - 1)
		{
			if (node[y][x].state != Wall)
			{
				node[startY][startX].state = Empty;
				toUpdeit.push_back(make_pair(startY, startX));
				startX = x;
				startY = y;
				toUpdeit.push_back(make_pair(y, x));
			}
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Right) && Keyboard::isKeyPressed(Keyboard::Key::LControl))
	{
		x = Mouse::getPosition(window).x / size;
		y = Mouse::getPosition(window).y / size;
		if (x > 0 && x < boardSize - 1 && y>0 && y < boardSize - 1)
		{
			if (node[y][x].state != Wall)
			{
				node[endY][endX].state = Empty;
				toUpdeit.push_back(make_pair(endY, endX));
				endX = x;
				endY = y;
				toUpdeit.push_back(make_pair(y, x));
			}
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Left))
	{
		x = Mouse::getPosition(window).x / size;
		y = Mouse::getPosition(window).y / size;

		if (x > 0 && x < boardSize - 1 && y>0 && y < boardSize - 1)
		{
			node[y][x].state = Wall;
			toUpdeit.push_back(make_pair(y, x));
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Right))
	{
		x = Mouse::getPosition(window).x / size;
		y = Mouse::getPosition(window).y / size;
		if (x > 0 && x < boardSize - 1 && y>0 && y < boardSize - 1)
		{
			node[y][x].state = Empty;
			toUpdeit.push_back(make_pair(y, x));
		}
	}
}
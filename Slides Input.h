#pragma once
#include "Board.h"

inline void Board::Slides_Input(RenderWindow& window)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{

		//sliders
		if (menu.setObsticalesSlide.Clicked(window))
		{
			int chance = menu.setObsticalesSlide.Value();
			for (int i = 0; i < boardSize; i++)
			{
				for (int j = 0; j < boardSize; j++)
				{
					int temp = rand() % 100;
					if (node[i][j].state != Start && node[i][j].state != End)
					{
						if (i != 0 && i != boardSize - 1 && j != 0 && j != boardSize - 1)
							node[i][j].state = Empty;//-to delete tge prevuis obsticales
						toUpdeit.push_back(make_pair(i, j));
						if (temp < chance)
						{
							node[i][j].state = Wall;
							toUpdeit.push_back(make_pair(i, j));
						}
					}

				}
			}
			Clear();
			UpdateAndDraw(window);
		}
		if (menu.setSizeSlide.Clicked(window))
		{
			printf(" %d %d\n", window.getSize().x, window.getSize().y);
			int nSize = menu.setSizeSlide.Value() * ((window.getSize().y / 100) / 5) + 5;
			if (nSize % 2 == 0)
				nSize++;
			if (endX > nSize - 2 || endY > nSize - 2)
			{
				endX = nSize - 2;
				endY = nSize - 2;
			}
			if (startX > nSize - 2 || startY > nSize - 2)
			{
				startX = 1;
				startY = 1;
			}
			vector<pair<int, int>>walls;
			string s = to_string(boardSize);
			string result = "Change Size\t" + s + "x" + s;
			menu.setSizeText.setString(result);
			for (int i = 0; i < boardSize; i++)
			{
				for (int j = 0; j < boardSize; j++)
				{
					if (node[i][j].state == Wall && i != 0 && j != 0 && i != boardSize - 1 && j != boardSize - 1)
						walls.push_back(make_pair(i, j));
				}
			}
			SetBoard(nSize, startX, startY, endX, endY, window.getSize().y, window.getSize().x, walls);
		}
		if (menu.setSpeedSlide.Clicked(window))
		{
			speed = menu.setSpeedSlide.Value() + 1;
			menu.setSpeedText.setString("Set Speed\tx" + to_string(speed));
		}
	}
}
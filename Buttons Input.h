#pragma once
#include"Board.h"

inline void Board::Buttons_Input(RenderWindow& window)
{
	if (menu.findButton.IsButtonPressed(window))
	{
		Clear();
		if (menu.bfs.chosen)
			BFS(window);
		else if (menu.a_star.chosen)
			A_Star(window);
		return;
	}
	if (menu.bfs.IsButtonPressed(window))
	{
		menu.bfs.chosen = true;
		menu.a_star.chosen = false;
	}
	if (menu.a_star.IsButtonPressed(window))
	{
		menu.bfs.chosen = false;
		menu.a_star.chosen = true;
	}

	//mazes
	if (menu.generateMazeButton.IsButtonPressed(window))
	{
		if (menu.mazeBackTracking.chosen)
			MazeGenerator_BackTracking(window);
		else if (menu.mazeSidewalker.chosen)
			MazeGenerator_Sidewinder(window);
		else if (menu.mazePrim.chosen)
			MazeGenerator_Prim(window);
	}
	if (menu.mazeBackTracking.IsButtonPressed(window))
	{
		menu.mazeBackTracking.chosen = true;
		menu.mazeSidewalker.chosen = false;
		menu.mazePrim.chosen = false;
	}
	if (menu.mazeSidewalker.IsButtonPressed(window))
	{
		menu.mazeBackTracking.chosen = false;
		menu.mazeSidewalker.chosen = true;
		menu.mazePrim.chosen = false;
	}
	if (menu.mazePrim.IsButtonPressed(window))
	{
		menu.mazeBackTracking.chosen = false;
		menu.mazeSidewalker.chosen = false;
		menu.mazePrim.chosen = true;
	}

	if (menu.clearButton.IsButtonPressed(window))
	{
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				if (i > 0 && i < boardSize - 1 && j>0 && j < boardSize - 1)
				{
					node[i][j].state = Empty;
					toUpdeit.push_back(make_pair(i, j));
				}
			}
		}
		toAnimate = true;
	}
	if (menu.exitButton.IsButtonPressed(window))
	{
		toEnd = true;
	}
	if (menu.toDrawEdgesButton.IsButtonPressed(window))
	{

		menu.notDrawEdgesButton.chosen = false;
		menu.toDrawEdgesButton.chosen = true;
		if (menu.toDrawEdgesButton.chosen)
		{
			int index = 0;
			for (int i = 0; i < boardSize; i++)
			{
				for (int j = 0; j < boardSize; j++)
				{
					ver_arr[index].position.x = j * size;
					ver_arr[index].position.y = i * size;
					index++;
					ver_arr[index].position.x = j * size + size - 1;
					ver_arr[index].position.y = i * size;
					index++;
					ver_arr[index].position.x = j * size + size - 1;
					ver_arr[index].position.y = i * size + size - 1;
					index++;
					ver_arr[index].position.x = j * size;
					ver_arr[index].position.y = i * size + size - 1;
					index++;
				}
			}
		}

	}
	if (menu.notDrawEdgesButton.IsButtonPressed(window))
	{
		menu.notDrawEdgesButton.chosen = true;
		menu.toDrawEdgesButton.chosen = false;
		if (menu.notDrawEdgesButton.chosen)
		{
			menu.toDrawEdgesButton.chosen = false;
			int index = 0;
			for (int i = 0; i < boardSize; i++)
			{
				for (int j = 0; j < boardSize; j++)
				{
					ver_arr[index].position.x = j * size;
					ver_arr[index].position.y = i * size;
					index++;
					ver_arr[index].position.x = j * size + size;
					ver_arr[index].position.y = i * size;
					index++;
					ver_arr[index].position.x = j * size + size;
					ver_arr[index].position.y = i * size + size;
					index++;
					ver_arr[index].position.x = j * size;
					ver_arr[index].position.y = i * size + size;
					index++;
				}
			}
		}
	}
}
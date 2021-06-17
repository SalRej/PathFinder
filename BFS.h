#pragma once
#include "Board.h"

// 1. push start node into open set
// 2. chek all it's neighbors and set it's parrent to be the current cell
// 3 repeat for all neighbor util the current cells is the end
inline bool Board::Chek_Neighbors(RenderWindow& window)
{

	std::stack<int>OpenSetX = {};
	std::stack<int>OpenSetY = {};

	std::stack<int>ClosedSetX = {};
	std::stack<int>ClosedSetY = {};

	OpenSetX.push(startX);
	OpenSetY.push(startY);

	while (1)
	{
		if (OpenSetX.size() == 0)
			return false;
		while (OpenSetX.size() > 0)
		{

			int y = OpenSetY.top(), x = OpenSetX.top();
			for (int i = 0; i < node[y][x].neighbors.size(); i++)
			{
				int neighbor_y = node[y][x].neighbors[i].first;
				int neighbor_x = node[y][x].neighbors[i].second;

				if (node[neighbor_y][neighbor_x].state != Wall &&
					node[neighbor_y][neighbor_x].state != Visited)
				{
					if (node[neighbor_y][neighbor_x].state == End)
					{
						node[neighbor_y][neighbor_x].ParentX = x;
						node[neighbor_y][neighbor_x].ParentY = y;
						return true;
					}

					node[neighbor_y][neighbor_x].ParentX = x;
					node[neighbor_y][neighbor_x].ParentY = y;
					node[neighbor_y][neighbor_x].state = Visited;
					toUpdeit.push_back(make_pair(neighbor_y, neighbor_x));

					ClosedSetY.push(neighbor_y);
					ClosedSetX.push(neighbor_x);
				}
			}

			OpenSetX.pop();
			OpenSetY.pop();
		}

		while (ClosedSetX.size() > 0)
		{
			OpenSetX.push(ClosedSetX.top());
			OpenSetY.push(ClosedSetY.top());
			ClosedSetX.pop();
			ClosedSetY.pop();
		}
		if (toAnimate)
		{
			speed_counter++;
			if (speed_counter >= speed)
			{
				speed_counter = 0;
				UpdateAndDraw(window);
			}
		}
	}
	return false;
}
inline void Board::BFS(RenderWindow& window)
{
	node[startY][startX].state = Start;
	node[endY][endX].state = End;

	if (Chek_Neighbors(window))
	{
		toAnimate = false;

		int tempX, tempY;
		//kordinati da zapomnqt kordinatite na Enda zakvoto she gi zagubq v slaedvashtiq cikyl
		int endx = endX, endy = endY;
		path.push_back(make_pair(endy, endx));

		//vkarvam koordinatite v masivte Path x/y
		while (1)
		{
			tempX = endx;
			tempY = endy;

			if (tempX == startX && tempY == startY)
			{
				break;
			}

			path.push_back(make_pair(node[tempY][tempX].ParentY, node[tempY][tempX].ParentX));

			endy = node[tempY][tempX].ParentY;
			endx = node[tempY][tempX].ParentX;
		}

		//chertq pytq
		for (int i = 0; i < path.size(); i++)
		{
			node[path[i].first][path[i].second].state = Path;
			toUpdeit.push_back(make_pair(path[i].first, path[i].second));
		}
	}
}

#pragma once
#include"Board.h"
using namespace std;
//cheks the current cell if it has any valid neighbors
inline bool HasNeigbors(pair<int, int>cordinates, Node** nodes, int n)
{
	n--;
	//up left
	if (cordinates.first - 2 < 0 && cordinates.second - 2 < 0)
	{
		if (
			nodes[cordinates.first + 2][cordinates.second].state == Wall ||
			nodes[cordinates.first][cordinates.second + 2].state == Wall
			)
			return true;
	}
	//down left
	else if (cordinates.first + 2 > n && cordinates.second - 2 < 0)
	{
		if (
			nodes[cordinates.first - 2][cordinates.second].state == Wall ||
			nodes[cordinates.first][cordinates.second + 2].state == Wall
			)
			return true;
	}
	//up right
	else if (cordinates.first - 2 < 0 && cordinates.second + 2 > n)
	{
		if (
			nodes[cordinates.first + 2][cordinates.second].state == Wall ||
			nodes[cordinates.first][cordinates.second - 2].state == Wall)
			return true;
	}
	//down right
	else if (cordinates.first + 2 > n && cordinates.second + 2 > n)
	{
		if (
			nodes[cordinates.first - 2][cordinates.second].state == Wall ||
			nodes[cordinates.first][cordinates.second - 2].state == Wall)
			return true;
	}
	//left
	else if (cordinates.first - 2 < 0)
	{
		if (nodes[cordinates.first + 2][cordinates.second].state == Wall ||
			nodes[cordinates.first][cordinates.second + 2].state == Wall ||
			nodes[cordinates.first][cordinates.second - 2].state == Wall)
			return true;
	}
	//right
	else if (cordinates.first + 2 > n)
	{
		if (nodes[cordinates.first - 2][cordinates.second].state == Wall ||
			nodes[cordinates.first][cordinates.second + 2].state == Wall ||
			nodes[cordinates.first][cordinates.second - 2].state == Wall)
			return true;
	}
	//up
	else if (cordinates.second - 2 < 0)
	{
		if (nodes[cordinates.first + 2][cordinates.second].state == Wall ||
			nodes[cordinates.first - 2][cordinates.second].state == Wall ||
			nodes[cordinates.first][cordinates.second + 2].state == Wall)
			return true;
	}
	//down
	else if (cordinates.second + 2 > n)
	{
		if (nodes[cordinates.first + 2][cordinates.second].state == Wall ||
			nodes[cordinates.first - 2][cordinates.second].state == Wall ||
			nodes[cordinates.first][cordinates.second - 2].state == Wall)
			return true;
	}
	else if (nodes[cordinates.first + 2][cordinates.second].state == Wall ||
		nodes[cordinates.first - 2][cordinates.second].state == Wall ||
		nodes[cordinates.first][cordinates.second + 2].state == Wall ||
		nodes[cordinates.first][cordinates.second - 2].state == Wall)
		return true;

	return false;
}

//it's like bfs but for maze 
//push start cell into vector with neighbors
//take a cell with valid neighbors and push it's neighbors into the vector
//do until the vector has size > 0
inline void Board::MazeGenerator_Prim(RenderWindow& window)
{
	//clearing the paths
	path.clear();
	//setting all cells to be walls
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (i > 0 && i < boardSize - 1 && j>0 && j < boardSize - 1)
			{
				node[i][j].state = Wall;
				toUpdeit.push_back(make_pair(i, j));
			}
		}
	}
	UpdateAndDraw(window);
	//vector which contains evry cell with valid neighbors
	vector<pair<int, int>>cells_with_neighbors;

	cells_with_neighbors.push_back(make_pair(1, 1));
	node[1][1].state = Empty;
	toUpdeit.push_back(make_pair(1, 1));

	while (cells_with_neighbors.size() > 0)
	{
		//chose random neighbor
		int index = rand_range(0, cells_with_neighbors.size() - 1);
		int currnet_y = cells_with_neighbors[index].first;
		int currnet_x = cells_with_neighbors[index].second;

		//+ 2 becouse it has to be an odd index
		int left = currnet_x - 2;
		int right = currnet_x + 2;
		int up = currnet_y - 2;
		int down = currnet_y + 2;
		int rand = rand_range(0, 3);

		switch (rand)
		{
		case 0:
		{
			//to see if it is outside of array bounds
			if (left > 0)
			{
				if (node[currnet_y][left].state == Wall)
				{
					//make the 2 cells next to it empty and pushing the next odd one into the cells with valid neighbors
					node[currnet_y][left + 1].state = Empty;
					node[currnet_y][left].state = Empty;

					toUpdeit.push_back(make_pair(currnet_y, left+1));
					toUpdeit.push_back(make_pair(currnet_y, left));

					cells_with_neighbors.push_back(make_pair(currnet_y, left));
				}
			}
		}break;
		case 1:
		{
			if (right < boardSize - 1)
			{
				if (node[currnet_y][right].state == Wall)
				{
					node[currnet_y][right - 1].state = Empty;
					node[currnet_y][right].state = Empty;

					toUpdeit.push_back(make_pair(currnet_y, right - 1));
					toUpdeit.push_back(make_pair(currnet_y, right));

					cells_with_neighbors.push_back(make_pair(currnet_y, right));
				}
			}
		}break;
		case 2:
		{

			if (up > 0)
			{
				if (node[up][currnet_x].state == Wall)
				{
					node[up + 1][currnet_x].state = Empty;
					node[up][currnet_x].state = Empty;

					toUpdeit.push_back(make_pair(up + 1, currnet_x));
					toUpdeit.push_back(make_pair(up, currnet_x));

					cells_with_neighbors.push_back(make_pair(up, currnet_x));
				}
			}
		}break;
		case 3:
		{

			if (down < boardSize - 1)
			{
				if (node[down][currnet_x].state == Wall)
				{
					node[down - 1][currnet_x].state = Empty;
					node[down][currnet_x].state = Empty;

					toUpdeit.push_back(make_pair(down - 1, currnet_x));
					toUpdeit.push_back(make_pair(down, currnet_x));

					cells_with_neighbors.push_back(make_pair(down, currnet_x));
				}

			}
		}break;
		default:
			break;
		}

		//clearing all cells with no more valid neigbors
		for (int i = 0; i < cells_with_neighbors.size(); i++)
		{
			if (!HasNeigbors(cells_with_neighbors[i], node, boardSize))
			{
				cells_with_neighbors.erase(cells_with_neighbors.begin() + i);
			}
		}
		speed_counter++;
		if (speed_counter >= speed)
		{
			speed_counter = 0;
			UpdateAndDraw(window);
		}
	}
	node[startY][startX].state = Start;
	node[endY][endX].state = End;
	toAnimate = true;
}

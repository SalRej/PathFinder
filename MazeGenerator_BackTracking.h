#pragma once
#include "Board.h"

//1 push first cell
//2 chose random neighbor and go there if it's not an empty space
//3 if all neighbors are empty cells backtrack until a neighbor has an enpty cell
//4 do until the stack is empty 
inline void Board::MazeGenerator_BackTracking(RenderWindow& window)
{

	//clearing the paths 
	path.clear();

	//set every cell as a wall
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			node[i][j].state = Wall;
			toUpdeit.push_back(make_pair(i, j));
		}
	}

	stack<int>x, y;
	//push 1 1 as a starting point
	x.push(1);
	y.push(1);

	bool finish = false;

	while (!finish)
	{
		//nodes to be cheked
		int current_i = y.top();
		int current_j = x.top();
		int size = node[current_i][current_j].neighbors.size();

		//idnex of neighbors which i have visited
		vector<int>visited;
		while (1)
		{
			//chosing a random neighbor
			int index = rand() % size;

			//if not all neighbots are visited
			if (visited.size() < size)
			{
				for (int i = 0; i < visited.size(); i++)
				{
					//if i have visited this neighbor then cose another random one 
					if (visited[i] == index)
					{
						index = rand() % size;

					}
				}
				visited.push_back(index);
			}
			else
			{

				x.pop();
				y.pop();
				if (x.size() == 0)
				{
					finish = true;
					break;
				}
				current_i = y.top();
				current_j = x.top();
				size = node[current_i][current_j].neighbors.size();
				visited.clear();
				break;
			}

			int neighbor_i = node[current_i][current_j].neighbors[index].first;
			int neighbor_j = node[current_i][current_j].neighbors[index].second;

			node[current_i][current_j].state = Empty;
			toUpdeit.push_back(make_pair(current_i, current_j));

			int directionX = neighbor_j - current_j;
			int directionY = neighbor_i - current_i;

			if (node[neighbor_i + directionY][neighbor_j + directionX].state == Wall)
			{
				node[neighbor_i][neighbor_j].state = Empty;
				node[neighbor_i + directionY][neighbor_j + directionX].state = Empty;
				toUpdeit.push_back(make_pair(neighbor_i, neighbor_j));
				toUpdeit.push_back(make_pair(neighbor_i + directionY, neighbor_j+directionX));

				x.push(neighbor_j + directionX);
				y.push(neighbor_i + directionY);
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			break;
		speed_counter++;
		if (speed_counter >= speed)
		{
			speed_counter = 0;
			UpdateAndDraw(window);
		}
	}

	node[startY][startX].state=Start;
	node[endY][endX].state = End;
	toAnimate = true;
}


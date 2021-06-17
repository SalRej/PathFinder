#pragma once
#include "Board.h"
#include <list>

//1.push first node
//2.chek it's neighbors and calculate f,g,h
//2.if it's not int the open set push it 
//3.take the lowest f from open set if f==f the pick lowest h
//4.remove the current node from the open set
//5.repeat from step 2
//if current node is edn stop

using namespace std;
float dist(int x, int y, int x2, int y2)
{
	//return sqrt(pow(x - x2, 2) + pow(y - y2, 2));
	return abs(x - x2) + abs(y - y2);
}
inline void Board::A_Star(RenderWindow& window)
{
	//calculate f,g,h for start node
	node[startY][startX].g = 0;
	node[startY][startX].h = dist(startX, startY, endX, endY);
	node[startY][startX].f = node[startY][startX].g + node[startY][startX].h;

	vector<pair<int, int>>open_set;
	open_set.push_back(make_pair(startY, startX));

	while (open_set.size() > 0)
	{
		//
		int current_x = open_set[0].second;
		int current_y = open_set[0].first;
		int index = 0; //to know which cell to delete at the end
		//pick the one with lowest f value
		for (int i = 0; i < open_set.size(); i++)
		{
			int chek_x = open_set[i].second;
			int chek_y = open_set[i].first;
			if (node[current_y][current_x].f == node[chek_y][chek_x].f)
			{
				if (node[current_y][current_x].h > node[chek_y][chek_x].h)
				{
					current_y = chek_y;
					current_x = chek_x;
					index = i;
				}
			}
			else if (node[current_y][current_x].f > node[chek_y][chek_x].f)
			{
				current_y = chek_y;
				current_x = chek_x;
				index = i;
			}
		}

		open_set.erase(open_set.begin() + index);

		//if it's the end stop
		if (node[current_y][current_x].state == End)
		{

			//backtrack
			int tempX, tempY;
			//kordinati da zapomnqt kordinatite na Enda zakvoto she gi zagubq v slaedvashtiq cikyl
			int endx = endX, endy = endY;
			path.push_back(make_pair(endY,endx));
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
			}

			toAnimate = false;

			return;
		}
		//mark the current cell as visited
		node[current_y][current_x].state = Visited;
		toUpdeit.push_back(make_pair(current_y, current_x));

		//calculate f,g,h for all neighbors of the current cell
		for (int i = 0; i < node[current_y][current_x].neighbors.size(); i++)
		{
			int neighbor_x = node[current_y][current_x].neighbors[i].second;
			int neighbor_y = node[current_y][current_x].neighbors[i].first;

			if (node[neighbor_y][neighbor_x].state != Visited && node[neighbor_y][neighbor_x].state != Wall)
			{
				//new distance from the start to the neighbor if ti is less then the current one then chage it
				float tempG = node[current_y][current_x].g + 1;
			
				if (tempG < node[neighbor_y][neighbor_x].g)
				{
					node[neighbor_y][neighbor_x].ParentX = current_x;
					node[neighbor_y][neighbor_x].ParentY = current_y;
					node[neighbor_y][neighbor_x].g = tempG;
					node[neighbor_y][neighbor_x].h = dist(neighbor_x, neighbor_y, endX, endY);
					node[neighbor_y][neighbor_x].f = node[neighbor_y][neighbor_x].g + node[neighbor_y][neighbor_x].h;

					//chek if it contains the neighbor in the open set
					if (!count(open_set.begin(), open_set.end(), make_pair(neighbor_y, neighbor_x)))
					{
						open_set.push_back(make_pair(neighbor_y, neighbor_x));

					}
				}
			}

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

}
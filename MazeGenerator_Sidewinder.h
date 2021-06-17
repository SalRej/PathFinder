#pragma once
#include<random>
#include"Board.h"
inline int rand_range(int begin, int end)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(begin, end);

	return distr(gen);
}

//1. make the firs row empty 
//2. on the next one (has to be odd index) with random chance carve right
//3. if chance says to stop pich a random spot from where you startted to carve till the spot where you are now and make a hole on te row above
//4. do till the end of the array
inline void Board::MazeGenerator_Sidewinder(RenderWindow& window)
{
	//clearing the paths 
	path.clear();
	
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
	//first row is empty
	for (int i = 1; i < boardSize -1 ; i++)
	{
		node[1][i].state = Empty;
		toUpdeit.push_back(make_pair(1, i));

	}
	UpdateAndDraw(window);

	//starts from the 3th one becouse it always has to be an odd index
	for (int i = 3; i < boardSize; i += 2)
	{
		//the index from where i have to chose a random passage 
		int last_x = 1;
		for (int j = 1; j < boardSize; j++)
		{
			speed_counter++;
			if (speed_counter >= speed)
			{
				speed_counter = 0;
				UpdateAndDraw(window);
			}

			//if 0 dont make a hole else if i then make a hole
			int to_carve = rand_range(0, 1);

			
			//dont make hole on a even cell
			if (j % 2 == 0)
			{
				node[i][j].state = Empty;
				toUpdeit.push_back(make_pair(i, j));

			}
			else
			{
				// to make sure the last section has a hole too 
				if (j == boardSize - 2)
				{
					to_carve = 1;
				}

				if (to_carve == 0)
				{
					node[i][j].state = Empty;
					toUpdeit.push_back(make_pair(i, j));
				}
				else
				{
					//chose random hole (has to be odd num)
					int holeX = rand_range(last_x, j);
					while (holeX % 2 == 0) holeX = rand_range(last_x, j);

					node[i][j].state = Empty;
					node[i - 1][holeX].state = Empty;

					toUpdeit.push_back(make_pair(i, j));
					toUpdeit.push_back(make_pair(i - 1, j));

					j++;
					//j+1 becouse i have to leave 1 wall
					last_x = j + 1;
				}
			}
		}
	}
	node[startY][startX].state = Start;
	node[endY][endX].state = End;
	toAnimate = true;
}
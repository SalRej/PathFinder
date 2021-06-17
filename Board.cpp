#pragma once
#include "Board.h"
#include "BFS.h"
#include "A_Star.h"
#include"MazeGenerator_Sidewinder.h"
#include"MazeGenerator_BackTracking.h"
#include"MazeGenerator_Prim.h"
#include "Input.h"
void Board::SetNeighbors()
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (i == 1 && j == 1)
			{
				node[i][j].neighbors.push_back(make_pair(i, j + 1));
				node[i][j].neighbors.push_back(make_pair(i + 1, j));
			}
			else if (i == boardSize - 2 && j == 1)
			{
				node[i][j].neighbors.push_back(make_pair(i, j + 1));
				node[i][j].neighbors.push_back(make_pair(i - 1, j));
			}
			else if (i == boardSize - 2 && j == boardSize - 2)
			{
				node[i][j].neighbors.push_back(make_pair(i - 1, j));
				node[i][j].neighbors.push_back(make_pair(i, j - 1));
			}
			else if (i == 1 && j == boardSize - 2)
			{
				node[i][j].neighbors.push_back(make_pair(i + 1, j));
				node[i][j].neighbors.push_back(make_pair(i, j - 1));
			}
			else if (i == 1)
			{
				node[i][j].neighbors.push_back(make_pair(i + 1, j));
				node[i][j].neighbors.push_back(make_pair(i, j + 1));
				node[i][j].neighbors.push_back(make_pair(i, j - 1));
			}
			else if (i == boardSize - 2)
			{
				node[i][j].neighbors.push_back(make_pair(i - 1, j));
				node[i][j].neighbors.push_back(make_pair(i, j + 1));
				node[i][j].neighbors.push_back(make_pair(i, j - 1));
			}
			else if (j == 1)
			{
				node[i][j].neighbors.push_back(make_pair(i + 1, j));
				node[i][j].neighbors.push_back(make_pair(i, j + 1));
				node[i][j].neighbors.push_back(make_pair(i - 1, j));
			}
			else if (j == boardSize - 2)
			{
				node[i][j].neighbors.push_back(make_pair(i + 1, j));
				node[i][j].neighbors.push_back(make_pair(i, j - 1));
				node[i][j].neighbors.push_back(make_pair(i - 1, j));
			}
			else
			{
				node[i][j].neighbors.push_back(make_pair(i + 1, j));
				node[i][j].neighbors.push_back(make_pair(i - 1, j));
				node[i][j].neighbors.push_back(make_pair(i, j + 1));
				node[i][j].neighbors.push_back(make_pair(i, j - 1));
			}
		}
	}
}
void Board::SetBoard(int newBoardSize, int sX, int sY, int eX, int eY,int window_h,int window_w,vector<pair<int,int>>walls)
{
	//it's a bit ugly but i does the job for know 
	for (int i = 0; i < boardSize; i++)
	{
		delete[] node[i];
	}
	delete[] node;

	boardSize = newBoardSize;
	startX = sX, startY = sY;
	endX = eX, endY = eY;
	node = new Node * [boardSize];
	for (int i = 0; i < boardSize; i++)
	{
		node[i] = new Node[boardSize];
	}

	ver_arr.resize(boardSize * boardSize * 4);
	ver_arr.setPrimitiveType(Quads);

	size = (float)window_h / boardSize;
	int index = 0;
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (i == 0 || i == boardSize - 1 || j == 0 || j == boardSize - 1)
			{
				node[i][j].state = Wall;
				toUpdeit.push_back(make_pair(i,j));
			}
			else
			{
				node[i][j].state = Empty;
				toUpdeit.push_back(make_pair(i, j));
			}

			if (menu.toDrawEdgesButton.chosen)
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
			else if (menu.notDrawEdgesButton.chosen)
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

	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i].first < boardSize - 1 && walls[i].second < boardSize - 1)
		{
			node[walls[i].first][walls[i].second].state = Wall;
			toUpdeit.push_back(make_pair(walls[i].first, walls[i].second));
		}
	}
	SetNeighbors();
	node[sY][sX].state = Start;
	node[eY][eX].state = End;
	toUpdeit.push_back(make_pair(sY, sX));
	toUpdeit.push_back(make_pair(eY, eX));
}
Board::Board(int size_borad,int sX, int sY, int eX, int eY,int wH,int wW)
{
	vector<pair<int, int>> v;//empty vector just to pass the function
	SetBoard(size_borad, sX, sY, eX, eY, wH,wW,v);
	menu.SetPosition(wH, 0);
	menu.SetSize(wW - wH, wH);
}
Board::~Board()
{
	for (int i = 0; i < boardSize; i++)
	{
		delete[] node[i];
	}
	delete[] node;
}

void Board::Clear()
{
	path.clear();
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (node[i][j].state != Wall)
			{
				if (node[i][j].state != Empty)//i don't want to updei empty cells
					toUpdeit.push_back(make_pair(i, j));
				node[i][j].state = Empty;
			}

			node[i][j].f = INFINITY;
			node[i][j].g = INFINITY;
			node[i][j].h = INFINITY;

		}
	}

	node[startY][startX].state = Start;
	node[endY][endX].state = End;
	toUpdeit.push_back(make_pair(startY, startX));
	toUpdeit.push_back(make_pair(endY, endX));

}
void Board::UpdateAndDraw(RenderWindow& window)
{
	int index = 0;

	for (int i = 0; i < path.size(); i++)
	{
		if (node[path[i].first][path[i].second].state != Wall &&
			node[path[i].first][path[i].second].state != Start &&
			node[path[i].first][path[i].second].state != End)
		{
			node[path[i].first][path[i].second].state = Path;

			toUpdeit.push_back(make_pair(path[i].first, path[i].second));
		}
	}

	for (int i = 0; i < toUpdeit.size(); i++)
	{
		int x = toUpdeit[i].second;
		int y = toUpdeit[i].first;

		int index = y * boardSize + x;
		index *= 4;
		if ((toUpdeit[i].second == startX && toUpdeit[i].first == startY) || (toUpdeit[i].second == endX && toUpdeit[i].first == endY))
		{
			ver_arr[index].color = Color::Red;
			index++;
			ver_arr[index].color = Color::Red;
			index++;
			ver_arr[index].color = Color::Red;
			index++;
			ver_arr[index].color = Color::Red;

		}
		else if (node[y][x].state == Empty)
		{
			ver_arr[index].color = Color::White;
			index++;
			ver_arr[index].color = Color::White;
			index++;
			ver_arr[index].color = Color::White;
			index++;
			ver_arr[index].color = Color::White;

		}
		else if (node[y][x].state == Visited)
		{
			ver_arr[index].color = Color::Green;
			index++;
			ver_arr[index].color = Color::Green;
			index++;
			ver_arr[index].color = Color::Green;
			index++;
			ver_arr[index].color = Color::Green;

		}
		else if (node[y][x].state == Path)
		{
			ver_arr[index].color = Color::Blue;
			index++;
			ver_arr[index].color = Color::Blue;
			index++;
			ver_arr[index].color = Color::Blue;
			index++;
			ver_arr[index].color = Color::Blue;
		}
		else if (node[y][x].state == Wall)
		{
			ver_arr[index].color = Color::Black;
			index++;
			ver_arr[index].color = Color::Black;
			index++;
			ver_arr[index].color = Color::Black;
			index++;
			ver_arr[index].color = Color::Black;
		}
	}
	toUpdeit.clear();

	window.clear(Color{ 100,100,100 });
	speed_counter = 0;
	window.draw(ver_arr);
	menu.Draw(window);
	window.display();

	//im giving control on the speed slide and the exit button while a maze is generating or path i searched
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		if (menu.setSpeedSlide.Clicked(window))
		{
			speed = menu.setSpeedSlide.Value();
		}
		if (menu.exitButton.IsButtonPressed(window))
		{
			exit(0);
		}
	}
}
void Board::Updeit(RenderWindow& window)
{
	if (toAnimate)
	{
		while(toAnimate)
		{
			if (toEnd)
			{
				window.close();
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
				window.close();

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			Input(window);
			Clear();
			UpdateAndDraw(window);


		}
	}
	else
	{
		if (toEnd)
		{
			window.close();
			return;
		}
		Input(window);
		Clear();
		if (toAnimate)
			return;

		if (menu.a_star.chosen)
			A_Star(window);
		else if (menu.bfs.chosen)
			BFS(window);
		UpdateAndDraw(window);

	}
}
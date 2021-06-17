#pragma once

#include "Menu.h"
#include<vector>
#include<stack>

using namespace sf;
using namespace std;
enum States { Wall, Empty, Start, End, Visited, Path };

class Node
{
public:

	int ParentX;
	int ParentY;
	vector<pair<int,int>>neighbors;
	States state;

	//for a*
	float f = 10000;
	float h = 10000;
	float g = 10000;
};
class Board
{
public:
	int boardSize;
	int startX, startY;
	int endX, endY;
	float size;

	// to close the app
	bool toEnd = false;
	//animate first time and after clear button 
	bool toAnimate = true;

	int speed = 1;//how often to draw 
	int speed_counter = 0;

	vector<pair<int,int>>path;
	//cell to updeit - ipdeiting only those wich have changed so i dont have to loop for all cells
	vector<pair<int, int>>toUpdeit;
	VertexArray ver_arr;//draw cells
	Menu menu;

public:
	Node** node;
	Board(int w, int sX, int sY, int eX, int eY,int window_h,int window_w);
	~Board();
	void UpdateAndDraw(RenderWindow&);
	bool Chek_Neighbors(RenderWindow&);
	void BFS(RenderWindow&);
	void A_Star(RenderWindow& window);
	void Input(RenderWindow&);
	void Slides_Input(RenderWindow& window);
	void Board_Input(RenderWindow& window);
	void Buttons_Input(RenderWindow& window);
	void Updeit(RenderWindow&);
	void SetNeighbors();
	void MazeGenerator_BackTracking(RenderWindow&);
	void MazeGenerator_Sidewinder(RenderWindow&);
	void MazeGenerator_Prim(RenderWindow&);

	void Clear();
	void SetBoard(int w, int sX, int sY, int eX, int eY,int window_h,int window_w,vector<pair<int,int>>walls);

};



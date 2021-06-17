#pragma once
#include"Slide.h"
#include"Button.h"
class Menu
{
	float positionX, positionY;
	float sizeX, sizeY;
public:

	//text for the slides
	Font arial;
	Text setSizeText;
	Text setObsticalesText;
	Text setSpeedText;

	//slides
	Slide setSizeSlide;
	Slide setObsticalesSlide;
	Slide setSpeedSlide;

	Button clearButton;

	//buttons for pathfinding
	Button findButton;
	Button bfs;
	Button a_star;

	//buttons for mazes
	Button generateMazeButton;
	Button mazeBackTracking;
	Button mazeSidewalker;
	Button mazePrim;

	Button exitButton;
	Texture exitTexture;

	Button toDrawEdgesButton;
	Button notDrawEdgesButton;

	Menu();
	void Draw(RenderWindow&);
	void SetPosition(float,float);
	void SetSize(float, float);
	void Arange();
};


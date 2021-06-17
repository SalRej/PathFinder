#include "Menu.h"


Menu::Menu()
{
	arial.loadFromFile("arial.ttf");
	setSizeText.setFont(arial);
	setObsticalesText.setFont(arial);
	setSpeedText.setFont(arial);

	setSizeText.setString("Chage Size");
	setObsticalesText.setString("Add Obsticales");
	setSpeedText.setString("Set Speed");

	//set pathfinding buttons text
	findButton.text.setString("Find");
	findButton.color = Color{ 226,164,0 };//orange
	bfs.text.setString("BFS");
	a_star.text.setString("A*");

	//set mazez buttons text
	generateMazeButton.text.setString("Generate Maze");
	generateMazeButton.color = Color{226,164,0};
	mazeBackTracking.text.setString("Backtracking");
	mazeSidewalker.text.setString("Sidewalker");
	mazePrim.text.setString("Prim");


	toDrawEdgesButton.text.setString("Draw walls");
	toDrawEdgesButton.chosen = true;
	notDrawEdgesButton.text.setString("Don't draw walls");
	clearButton.text.setString("Clear");
	clearButton.color = Color{ 226,164,0 };

	//exit button
	exitTexture.loadFromFile("ExitTexture.png");
	exitButton.button.setTexture(&exitTexture);
	exitButton.SetSize(70, 70);

}
void Menu::Arange()
{
	float offsetY = 70;
	float offsetX = 100;
	float middle = positionX + sizeX/2;
	float button_size = findButton.button.getSize().x;//dosent matter which button all are the same size
	float between = 20;
	float first_row_x = middle - button_size - between;
	float second_row_x = middle + between;

	exitButton.SetPosition(positionX + sizeX - 100, 50);

	//slides
	setSizeText.setPosition(Vector2f(positionX + offsetX, positionY + offsetY));
	setSizeSlide.SetPosition(positionX + offsetX, positionY + offsetY*2);
	setSizeSlide.SetSize(sizeX - offsetX*2);

	setObsticalesText.setPosition(Vector2f(positionX + offsetX, positionY + offsetY * 3));
	setObsticalesSlide.SetPosition(positionX + offsetX, positionY + offsetY* 4);
	setObsticalesSlide.SetSize(sizeX - offsetX*2);

	setSpeedText.setPosition(Vector2f(positionX + offsetX, positionY + offsetY*5));
	setSpeedSlide.SetPosition(positionX + offsetX, positionY + offsetY * 6);
	setSpeedSlide.SetSize(sizeX - offsetX * 2);

	clearButton.SetPosition(middle - button_size/2, positionY + offsetY * 7);

	//pathfinding buttons
	findButton.SetPosition(first_row_x, positionY + offsetY * 8);
	bfs.SetPosition(first_row_x, positionY + offsetY * 9);
	a_star.SetPosition(first_row_x, positionY + offsetY * 10);


	//mazes buttons
	generateMazeButton.SetPosition(second_row_x, positionY + offsetY * 8);
	mazeBackTracking.SetPosition(second_row_x, positionY + offsetY * 9);
	mazeSidewalker.SetPosition(second_row_x ,positionY + offsetY * 10);
	mazePrim.SetPosition(second_row_x, positionY + offsetY * 11);


	toDrawEdgesButton.SetPosition(first_row_x, positionY + offsetY * 13);
	notDrawEdgesButton.SetPosition(second_row_x, positionY + offsetY * 13);
}
void Menu::Draw(RenderWindow&window)
{
	window.draw(setSizeText);
	window.draw(setObsticalesText);
	window.draw(setSpeedText);

	clearButton.Draw(window);
	exitButton.Draw(window);

	setSizeSlide.Draw(window);
	setObsticalesSlide.Draw(window);
	setSpeedSlide.Draw(window);

	//paathfinding buttons
	findButton.Draw(window);
	bfs.Draw(window);
	a_star.Draw(window);

	//draw mzes buttons
	generateMazeButton.Draw(window);
	mazeBackTracking.Draw(window);
	mazeSidewalker.Draw(window);
	mazePrim.Draw(window);

	toDrawEdgesButton.Draw(window);
	notDrawEdgesButton.Draw(window);
}
void Menu::SetPosition(float x, float y)
{
	positionX = x, positionY = y;
	Arange();
}
void Menu::SetSize(float sizeX, float sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	Arange();
}

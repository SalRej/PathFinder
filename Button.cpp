#include "Button.h"

Button::Button()
{
	arial.loadFromFile("arial.ttf");
	text.setFont(arial);

	button.setSize(Vector2f(250, 40));
	color = Color::Red;
	button.setFillColor(color);
}

void Button::Draw(RenderWindow& window)
{

	if (chosen)
	{
		button.setOutlineColor(Color::Yellow);
		button.setOutlineThickness(3);
		button.setFillColor(Color::Black);
	}
	else if (Mouse::getPosition(window).x > button.getPosition().x && Mouse::getPosition(window).x <button.getPosition().x + button.getSize().x &&
		Mouse::getPosition(window).y > button.getPosition().y && Mouse::getPosition(window).y < button.getPosition().y + button.getSize().y)
	{
		button.setFillColor(Color::Green);
		button.setOutlineThickness(0);
	}
	else
	{
		button.setFillColor(color);
		button.setOutlineThickness(0);
	}

	window.draw(button);
	window.draw(text);
	
}
void Button::SetPosition(float x, float y)
{
	button.setPosition(Vector2f(x, y));
	text.setPosition(Vector2f(x, y));
}
void Button::SetSize(float x, float y)
{
	button.setSize(Vector2f(x, y));
}
bool Button::IsButtonPressed(RenderWindow&window)
{

	if (Mouse::getPosition(window).x > button.getPosition().x && Mouse::getPosition(window).x <button.getPosition().x + button.getSize().x &&
		Mouse::getPosition(window).y > button.getPosition().y && Mouse::getPosition(window).y < button.getPosition().y + button.getSize().y)
	{
		return true;
	}
	return false;
}
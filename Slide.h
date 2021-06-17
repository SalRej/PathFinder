//#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace sf;
inline float norm(float val, float min, float max)
{
	return (val - min) / (max - min);
}
inline float lerp(float norm, float min, float max)
{
	return (max - min) * norm + min;
}
inline float mape(float val, float sorceMin, float sorceMax, float destMin, float destMax)
{
	float n = norm(val, sorceMin, sorceMax);
	return lerp(n, destMin, destMax);
}

class Slide
{
	RectangleShape line;
	RectangleShape button;
	float length;
	float button_size;
	float position_x, position_y;

public:
	Slide()
	{
		length = 100;
		button_size = 20;
		position_x = 0, position_y = 0;
		line.setPosition(Vector2f(position_x, position_y));
		button.setPosition(Vector2f(position_x, position_y - button_size / 2));
		button.setSize(Vector2f(button_size, button_size));
		button.setFillColor(Color::Red);
		line.setSize(Vector2f(length, 3));
	}
	void SetPosition(float x,float y)
	{
		position_x = x;
		position_y = y;

		line.setPosition(Vector2f(position_x, position_y));
		button.setPosition(Vector2f(position_x, position_y - button_size / 2));
	}
	void SetButtonSize(float size)
	{
		button_size = size;
		button.setSize(Vector2f(size, size));
	}
	void SetSize(float size)
	{
		length = size;
		line.setSize(Vector2f(length, 3));
	}
	int Value()
	{
		int temp = button.getPosition().x;
		return mape(temp, position_x, position_x+length - button_size, 0, 100);
	}
	bool Clicked(RenderWindow &window)
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			if (Mouse::getPosition(window).x > position_x && Mouse::getPosition(window).x < position_x+length &&
				Mouse::getPosition(window).y > button.getPosition().y && Mouse::getPosition(window).y < button.getPosition().y + button.getSize().y)
			{
				button.setFillColor(Color::Cyan);

				if(Mouse::getPosition().x>=position_x && Mouse::getPosition().x <= position_x+length)
					button.setPosition(Vector2f(Mouse::getPosition(window).x - button_size/2, button.getPosition().y));
				return true;
			}
			else
			{
				button.setFillColor(Color::Red);
				return false;
			}
		}
		return false;
	}
	void Draw(RenderWindow &window)
	{
		window.draw(line);
		window.draw(button);
	}
};
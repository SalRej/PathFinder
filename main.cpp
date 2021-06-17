#include "Board.h"

using namespace sf;

int main()
{
	const int W = VideoMode::getDesktopMode().width;
	const int H = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(W, H), "PahtFinding",Style::Fullscreen);
	window.setFramerateLimit(60);
	srand(time(0));
	Board Map(21, 1, 1, 19, 19, H, W);
	
	RectangleShape instructions;
	Texture instructions_texture;
	instructions_texture.loadFromFile("Instructions.png");
	instructions.setTexture(&instructions_texture);
	instructions.setSize(Vector2f(W, H));
	bool toStart = false;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
			window.close();

		if (toStart)
		{
			Map.Updeit(window);
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			{
				toStart = true;
			}
			window.draw(instructions);
			window.display();
		}

	}
	return 0;
}
//includes everything in SFML graphics reference
#include <SFML/Graphics.hpp>
//#include "ResourceManager\ResourceManager.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void ClampShape(sf::Shape& shape)
{
	auto shapePosition = shape.getPosition();
	auto bounds = shape.getGlobalBounds();
	if (bounds.left < 0)
	{
		shapePosition.x -= bounds.left;
	}
	if (bounds.top < 0)
	{
		shapePosition.y -= bounds.top;
	}
	if (bounds.left + bounds.width > WINDOW_WIDTH)
	{
		shapePosition.x -= ((bounds.left + bounds.width) - WINDOW_WIDTH);
	}
	if (bounds.top + bounds.height > WINDOW_HEIGHT)
	{
		shapePosition.y -= ((bounds.top + bounds.height) - WINDOW_HEIGHT);
	}
	shape.setPosition(shapePosition);
}

int main()
{
	/* Scrapped ResMan for now
	rm::ResourceManager::init(false);
	rm::Logger::setFileLocation("tests.txt");

	rm::ResourceManager::addResourceType<sf::Sprite>();
	*/

	sf::Texture texture;
	if (!texture.loadFromFile("pokemonMk1.png"))
	{
		// error...
	}

	//builds a window of certain size and name
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Final game engine club!");
	float rectSize = 100;

	//allocates a new shape in memory
	sf::RectangleShape shape(sf::Vector2f(rectSize, rectSize));
	shape.setTexture(&texture);
	shape.setOrigin(sf::Vector2f(rectSize / 2, rectSize));
	shape.setPosition(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
//	shape.setScale(sf::Vector2f(0.5f, 1.83482934982893472984f));

	while (window.isOpen())
	{
		sf::Event event;
		//checks for events
		while (window.pollEvent(event))
		{
			//checks for window X button click
			if (event.type == sf::Event::Closed) 
			{
				//closes it and makes the isOpen() return false
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					shape.setPosition(shape.getPosition() + sf::Vector2f(0.0f, -10.0f));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					shape.setPosition(shape.getPosition() + sf::Vector2f(0.0f, 10.0f));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					shape.setPosition(shape.getPosition() + sf::Vector2f(-10.0f, 0.0f));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					shape.setPosition(shape.getPosition() + sf::Vector2f(10.0f, 0.0f));
				}

				ClampShape(shape);
			}
		}

		//makes window blank
		window.clear();

		//adds to the render target
		window.draw(shape);

		//displays all that's in the render target
		window.display();
	}

	return 0;
}
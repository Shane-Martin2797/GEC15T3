//includes everything in SFML graphics reference
//#include <SFML/Graphics.hpp>
//#include "ResourceManager\ResourceManager.hpp"
#include <Box2D/Box2D.h>

#include <stdio.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

//void ClampShape(sf::Shape& shape)
//{
//	auto shapePosition = shape.getPosition();
//	auto bounds = shape.getGlobalBounds();
//	if (bounds.left < 0)
//	{
//		shapePosition.x -= bounds.left;
//	}
//	if (bounds.top < 0)
//	{
//		shapePosition.y -= bounds.top;
//	}
//	if (bounds.left + bounds.width > WINDOW_WIDTH)
//	{
//		shapePosition.x -= ((bounds.left + bounds.width) - WINDOW_WIDTH);
//	}
//	if (bounds.top + bounds.height > WINDOW_HEIGHT)
//	{
//		shapePosition.y -= ((bounds.top + bounds.height) - WINDOW_HEIGHT);
//	}
//	shape.setPosition(shapePosition);
//}

int main(int argc, char *argv[])
{
	/* Scrapped ResMan for now
	rm::ResourceManager::init(false);
	rm::Logger::setFileLocation("tests.txt");

	rm::ResourceManager::addResourceType<sf::Sprite>();
	*/

	//sf::Texture texture;
	//if (!texture.loadFromFile("pokemonMk1.png"))
	{
		// error...
	}

	//builds a window of certain size and name
	//sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Final game engine club!");
	float rectSize = 100;

	//allocates a new shape in memory
	//sf::RectangleShape shape(sf::Vector2f(rectSize, rectSize));
	//shape.setTexture(&texture);
	//shape.setOrigin(sf::Vector2f(rectSize / 2, rectSize));
	//shape.setPosition(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
//	shape.setScale(sf::Vector2f(0.5f, 1.83482934982893472984f));

	//while (window.isOpen())
	//{
	//	sf::Event event;
	//	//checks for events
	//	while (window.pollEvent(event))
	//	{
	//		//checks for window X button click
	//		if (event.type == sf::Event::Closed) 
	//		{
	//			//closes it and makes the isOpen() return false
	//			window.close();
	//		}
	//
	//		if (event.type == sf::Event::KeyPressed)
	//		{
	//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//			{
	//				shape.setPosition(shape.getPosition() + sf::Vector2f(0.0f, -10.0f));
	//			}
	//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//			{
	//				shape.setPosition(shape.getPosition() + sf::Vector2f(0.0f, 10.0f));
	//			}
	//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//			{
	//				shape.setPosition(shape.getPosition() + sf::Vector2f(-10.0f, 0.0f));
	//			}
	//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	//			{
	//				shape.setPosition(shape.getPosition() + sf::Vector2f(10.0f, 0.0f));
	//			}
	//
	//			ClampShape(shape);
	//		}
	//	}
	//
	//	//makes window blank
	//	window.clear();
	//
	//	//adds to the render target
	//	window.draw(shape);
	//
	//	//displays all that's in the render target
	//	window.display();
	//}
	//

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	
	return 0;
}
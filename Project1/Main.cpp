//includes everything in SFML graphics reference
#include <SFML/Graphics.hpp>
//#include "ResourceManager\ResourceManager.hpp"
#include <Box2D/Box2D.h>

#include <stdio.h>

#include "EntityFactory.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
class PhysicsClass
{
public:
	b2World* world = nullptr;
	float32 timeStep;

	int32 velocityIterations;
	int32 positionIterations;

	b2Body* body;
	b2Body* body2;


	PhysicsClass()
	{

	}


	int CreatePhysics()
	{


		// Define the gravity vector.
		b2Vec2 gravity(0.0f, 0.0f);

		// Construct a world object, which will hold and simulate the rigid bodies.
		world = new b2World(gravity);





		
		/*
		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef2;
		bodyDef2.type = b2_staticBody;
		bodyDef2.position.Set(300.0f, 200.0f);
		body2 = world->CreateBody(&bodyDef2);

		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox2;
		dynamicBox2.SetAsBox(1.0f, 1.0f);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef2;
		fixtureDef2.shape = &dynamicBox2;

		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef2.density = 1.0f;

		// Override the default friction.
		fixtureDef2.friction = 0.3f;

		// Add the shape to the body.
		body2->CreateFixture(&fixtureDef2);


	*/




		// Define the ground body.
		b2BodyDef groundBodyDef;
		groundBodyDef.type = b2_staticBody;
		groundBodyDef.position.Set(0.0f, 0.0f);
		b2Body* groundBody = world->CreateBody(&groundBodyDef);

		b2EdgeShape groundBox;

		b2FixtureDef boxShapeDef;

		groundBox.Set(b2Vec2(0, 0), b2Vec2(WINDOW_WIDTH, 0));

		boxShapeDef.shape = &groundBox;

		groundBody->CreateFixture(&boxShapeDef);
		
		groundBox.Set(b2Vec2(0, 0), b2Vec2(100, WINDOW_HEIGHT));
		groundBody->CreateFixture(&boxShapeDef);
		groundBox.Set(b2Vec2(0, WINDOW_HEIGHT), b2Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
		groundBody->CreateFixture(&boxShapeDef);
		groundBox.Set(b2Vec2(WINDOW_WIDTH-100,0), b2Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
		groundBody->CreateFixture(&boxShapeDef);

		
	

		// Add the ground fixture to the ground body.
		//groundBody->CreateFixture(&groundBox, 0.0f);







		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(300.0f, 400.0f);
		body = world->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(50.0f, 50.0f);

		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;

		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 3.0f;

		// Override the default friction.
		fixtureDef.friction = 0.0f;

		// Add the shape to the body.
		body->CreateFixture(&fixtureDef);



		// Prepare for simulation. Typically we use a time step of 1/60 of a
		// second (60Hz) and 10 iterations. This provides a high quality simulation
		// in most game scenarios.
		timeStep = 1.0f / 60.0f;
		velocityIterations = 6;
		positionIterations = 2;



		return 0;
	}

	void UpdatePhysics()
	{

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world->Step(timeStep, velocityIterations, positionIterations);
		body->ApplyForce(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, 0.0f), true);
	}
};

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


int main(int argc, char *argv[])
{

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	/* Scrapped ResMan for now
	rm::ResourceManager::init(false);
	rm::Logger::setFileLocation("tests.txt");

	rm::ResourceManager::addResourceType<sf::Sprite>();
	*/

	EntityFactory* entInstance = new EntityFactory();
	//entInstance->CreateComponent()

	delete entInstance;

	PhysicsClass instance = PhysicsClass();
	instance.CreatePhysics();

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
	shape.setOrigin(sf::Vector2f(rectSize / 2, rectSize/2));
	shape.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	//	shape.setScale(sf::Vector2f(0.5f, 1.83482934982893472984f));

	while (window.isOpen())
	{
		instance.UpdatePhysics();

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
					instance.world->SetGravity(instance.world->GetGravity() + b2Vec2(0.0f, -1.0f));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					instance.world->SetGravity(instance.world->GetGravity() + b2Vec2(0.0f, 1.0f));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					instance.world->SetGravity(instance.world->GetGravity() + b2Vec2(-1.0f, 0.0f));
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					instance.world->SetGravity(instance.world->GetGravity() + b2Vec2(1.0f, 0.0f));
				}

			//	ClampShape(shape);
			}
			
		}
		printf("%4.2f %4.2f %4.2f\n",instance.world->GetGravity().y);


		shape.setPosition(sf::Vector2f(instance.body->GetPosition().x, instance.body->GetPosition().y));
		//shape.setRotation(instance.body->GetAngle());

		//makes window blank
		window.clear();

		//adds to the render target
		window.draw(shape);

		//displays all that's in the render target
		window.display();
	}





}
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../ArknoidECS/Engine.h"
#include "../ArknoidECS/PaddleInputSystem.h"
#include "../ArknoidECS/BrickHitSystem.h"
#include "../ArknoidECS/PhysicsSystem.h"
#include "../ArknoidECS/ColliderDebugSystem.h"
#include "../ArknoidECS/MoveSystem.h"
#include "../ArknoidECS/RenderSystem.h"
#include "../ArknoidECS/physics.h"

void setup(World* world) {
	int wall_north = world->next_entity();
	world->masks[wall_north] |= COMP__TRANSFORM;
	world->transforms[wall_north].position.x = 0;
	world->transforms[wall_north].position.y = 0;
	world->masks[wall_north] |= COMP__BOX_COLLIDER;
	world->colliders[wall_north].extent.x = 640;
	world->colliders[wall_north].extent.y = 1;

	int wall_east = world->next_entity();
	world->masks[wall_east] |= COMP__TRANSFORM;
	world->transforms[wall_east].position.x = 640;
	world->transforms[wall_east].position.y = 0;
	world->masks[wall_east] |= COMP__BOX_COLLIDER;
	world->colliders[wall_east].extent.x = 1;
	world->colliders[wall_east].extent.y = 640;

	int wall_west = world->next_entity();
	world->masks[wall_west] |= COMP__TRANSFORM;
	world->transforms[wall_west].position.x = 0;
	world->transforms[wall_west].position.y = 0;
	world->masks[wall_west] |= COMP__BOX_COLLIDER;
	world->colliders[wall_west].extent.x = 1;
	world->colliders[wall_west].extent.y = 640;

	int wall_south = world->next_entity();
	world->masks[wall_south] |= COMP__TRANSFORM;
	world->transforms[wall_south].position.x = 0;
	world->transforms[wall_south].position.y = 480;
	world->masks[wall_south] |= COMP__BOX_COLLIDER;
	world->colliders[wall_south].extent.x = 640;
	world->colliders[wall_south].extent.y = 1;



	int ball = world->next_entity();
	world->masks[ball] |= COMP__TRANSFORM;
	world->transforms[ball].position.x = 300;
	world->transforms[ball].position.y = 300;

	world->masks[ball] |= COMP__SPRITE_CIRCLE;
	//world->sprites[ball].circle.setPosition({ 300, 300 });
	world->sprites[ball].circle.setRadius(15);
	world->sprites[ball].circle.setFillColor(sf::Color::Blue);

	world->masks[ball] |= COMP__SPEED;
	world->speeds[ball] = 300;

	world->masks[ball] |= COMP__RIGID_BODY;
	world->rbodies[ball].isKinematic = false;
	world->rbodies[ball].velocity.x = world->speeds[ball] * std::cos(60.f * 3.14f / 180);
	world->rbodies[ball].velocity.y = -world->speeds[ball] * std::sin(60.f * 3.14f / 180);
	//world->rbodies[ball].velocity.x = 0;
	//world->rbodies[ball].velocity.y = world->speeds[ball];
	//world->rbodies[ball].velocity.x = -200;
	//world->rbodies[ball].velocity.y = 0;

	world->masks[ball] |= COMP__BOX_COLLIDER;
	world->colliders[ball].extent.x = 15 * 2;
	world->colliders[ball].extent.y = 15 * 2;

	int paddle = world->next_entity();
	world->masks[paddle] |= COMP__TRANSFORM;
	//world->transforms[paddle].position.x = 100;
	//world->transforms[paddle].position.y = 310;
	world->transforms[paddle].position.x = 300;
	world->transforms[paddle].position.y = 400;
	world->masks[paddle] |= COMP__SPRITE_RECT;
	world->sprites[paddle].rect.setSize({ 100, 20 });
	world->sprites[paddle].rect.setFillColor(sf::Color::Red);
	world->masks[paddle] |= COMP__SPEED;
	world->speeds[paddle] = 250;
	world->masks[paddle] |= COMP__RIGID_BODY;
	world->rbodies[paddle].isKinematic = true;
	world->masks[paddle] |= COMP__KEYBOARD;
	world->masks[paddle] |= COMP__BOX_COLLIDER;
	world->colliders[paddle].extent.x = 100;
	world->colliders[paddle].extent.y = 20;

	for (int i = 0; i < 30; i++)
	{
		int row = i % 6 + 1;
		int col = i % 5 + 3;
		int brick = world->next_entity();
		world->masks[brick] |= COMPV__BRICK;
		world->masks[brick] |= COMP__TRANSFORM;
		world->transforms[brick].position.x = col * 60.f;
		world->transforms[brick].position.y = row * 30.f;
		world->masks[brick] |= COMP__SPRITE_RECT;
		world->sprites[brick].rect.setSize({ 50, 20 });

		world->masks[brick] |= COMP__BOX_COLLIDER;
		world->colliders[brick].extent.x = 50;
		world->colliders[brick].extent.y = 20;

		world->masks[brick] |= COMP__RESISTENCE;
		world->resistences[brick].hits = 0;
		if (i == 28) {
			world->sprites[brick].rect.setFillColor(sf::Color::Magenta);
			world->resistences[brick].hardiness = 3;
		}
		else {
			world->sprites[brick].rect.setFillColor(sf::Color::Green);
			world->resistences[brick].hardiness = 1;
		}

		world->masks[brick] |= COMP__SOUND;
		world->sounds[brick].file = "..\\sounds\\brick-ball-hit.wav";
		world->sounds[brick].buffer.loadFromFile("..\\sounds\\brick-ball-hit.wav");
		world->sounds[brick].audio.setBuffer(world->sounds[brick].buffer);
	}
}

int main() {
	Engine *engine = new Engine();
	World *world = new World();
	setup(world);

	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Arknoid-ECS");
	engine->window = &renderWindow;

	RenderSystem render;
	PaddleInputSystem keyboardSystem;
	PhysicsSystem physicsSystem;
	MoveSystem moveSystem;
	BrickHitSystem brickSystem;
	ColliderDebugSystem debugSystem;

	sf::Event event;
	// A Clock starts counting as soon as it's created
	sf::Clock clock;
	renderWindow.setFramerateLimit(60);
	while (renderWindow.isOpen()) {
		// Check for all the events that occured since the last frame.
		while (renderWindow.pollEvent(event)) {
			//Handle events here
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
		}

		float deltaTime = clock.restart().asSeconds();
		float frameRate = 1.f / deltaTime;

		engine->deltaTime = deltaTime;

		renderWindow.clear();

		physicsSystem.execute(world, engine);
		keyboardSystem.execute(world, engine);
		moveSystem.execute(world, engine);
		brickSystem.execute(world, engine);
		//debugSystem.execute(world, engine);
		render.execute(world, engine);

		renderWindow.display();
	}

	delete(world);
	delete(engine);
}

#include "PaddleInputSystem.h"
#include "SFML/Graphics.hpp"

void PaddleInputSystem::execute(World* aWorld, Engine* engine) {
	for (int i = 0; i < MAX_ENTITY_NUM; i++) {
		if (aWorld->has_component(i, COMP__KEYBOARD | COMP__SPEED | COMP__RIGID_BODY)) {
			float speed = aWorld->speeds[i];
			RigidBody& rbody = aWorld->rbodies[i];

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				//rbody.velocity.x = -speed * engine->deltaTime;
				rbody.velocity.x = -speed;
				rbody.velocity.y = 0.f;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				//rbody.velocity.x = speed * engine->deltaTime;
				rbody.velocity.x = speed;
				rbody.velocity.y = 0.f;
			}
			else {
				rbody.velocity.x = 0.f;
				rbody.velocity.y = 0.f;
			}
		}
	}
}
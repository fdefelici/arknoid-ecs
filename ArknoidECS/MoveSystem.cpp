#include "MoveSystem.h"

void MoveSystem::execute(World* aWorld, Engine* engine) {
	for (int i = 0; i < MAX_ENTITY_NUM; i++) {
		if (aWorld->has_component(i, COMP__RIGID_BODY | COMP__SPRITE_RECT | COMP__TRANSFORM)) {
			Transform& transf = aWorld->transforms[i];
			sf::RectangleShape& shape = aWorld->sprites[i].rect;
			//sf::Vector2f& velocity = aWorld->rbodies[i].velocity;
			/*
			if (transf.position.x <= 0.f && velocity.x < 0)
				velocity.x = 0;
			else if (transf.position.x + shape.getSize().x >= engine->window->getSize().x && velocity.x > 0)
				velocity.x = 0;
			*/
			//sf::Vector2f deltaTimed = velocity * engine->deltaTime;
			//transf.position += deltaTimed;
			shape.setPosition(transf.position);
			
			//shape.move(deltaTimed);
			//transf.position = shape.getPosition();
		}
		else if (aWorld->has_component(i, COMP__RIGID_BODY | COMP__SPRITE_CIRCLE | COMP__TRANSFORM)) {
			Transform& transf = aWorld->transforms[i];
			sf::CircleShape& shape = aWorld->sprites[i].circle;
			//sf::Vector2f& velocity = aWorld->rbodies[i].velocity;

			/*
			if (transf.position.x <= 0.f || transf.position.x + (shape.getRadius()*2.f) >= engine->window->getSize().x) {
				velocity.x *= -1.f;
			}
			if (transf.position.y <= 0.f || transf.position.y + (shape.getRadius()*2.f) >= engine->window->getSize().y) {
				velocity.y *= -1.f;
			}
			*/

			//sf::Vector2f deltaTimed = velocity * engine->deltaTime;
			//shape.move(deltaTimed);
			//atransf.position += deltaTimed;
			shape.setPosition(transf.position);
		}
	}
}
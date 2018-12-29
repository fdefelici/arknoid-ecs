#include "ColliderDebugSystem.h"

void ColliderDebugSystem::execute(World* aWorld, Engine* engine) {
	for (int i = 0; i < MAX_ENTITY_NUM; i++) {
		if (aWorld->has_component(i, COMP__BOX_COLLIDER)) {
			Transform& transfor = aWorld->transforms[i];
			BoxCollider& collider = aWorld->colliders[i];

			sf::RectangleShape shape;
			shape.setPosition(transfor.position);
			shape.setSize(collider.extent);
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineColor(sf::Color::Yellow);
			shape.setOutlineThickness(1.0f);
			engine->window->draw(shape);
		}
	}
}

#include "MoveSystem.h"

void MoveSystem::execute(World* aWorld, Engine* engine) {
	for (int i = 0; i < MAX_ENTITY_NUM; i++) {
		if (aWorld->has_component(i, COMP__RIGID_BODY | COMP__SPRITE_RECT | COMP__TRANSFORM)) {
			Transform& transf = aWorld->transforms[i];
			sf::RectangleShape& shape = aWorld->sprites[i].rect;
			shape.setPosition(transf.position);
		}
		else if (aWorld->has_component(i, COMP__RIGID_BODY | COMP__SPRITE_CIRCLE | COMP__TRANSFORM)) {
			Transform& transf = aWorld->transforms[i];
			sf::CircleShape& shape = aWorld->sprites[i].circle;
			shape.setPosition(transf.position);
		}
	}
}
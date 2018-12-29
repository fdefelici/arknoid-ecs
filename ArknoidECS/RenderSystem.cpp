#include "RenderSystem.h"

void RenderSystem::execute(World* aWorld, Engine* engine) {
	for (int i = 0; i < MAX_ENTITY_NUM; i++) {
		if (aWorld->has_component(i, COMP__SPRITE_RECT | COMP__TRANSFORM)) {
			Transform& transf = aWorld->transforms[i];
			aWorld->sprites[i].rect.setPosition(transf.position);
			engine->window->draw(aWorld->sprites[i].rect);
		}
		else if (aWorld->has_component(i, COMP__SPRITE_CIRCLE | COMP__TRANSFORM)) {
			Transform& transf = aWorld->transforms[i];
			aWorld->sprites[i].circle.setPosition(transf.position);
			engine->window->draw(aWorld->sprites[i].circle);
		}
	}
}

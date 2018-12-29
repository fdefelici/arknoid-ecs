#include "BrickHitSystem.h"
#include <iostream>

void BrickHitSystem::execute(World* aWorld, Engine* engine) {
	for (int i = 0; i < MAX_ENTITY_NUM; i++) {
		if (aWorld->has_component(i, COMPV__BRICK)) {
			if (aWorld->colliders[i].collision.has_begun) {
				std::cout << "COLPITO" << std::endl;
				HitResistance& resist = aWorld->resistences[i];
				resist.hits++;

				Sound& hit_sound = aWorld->sounds[i];
				hit_sound.audio.play();

				if (resist.hits >= resist.hardiness)
					aWorld->masks[i] = DESTROY_MASK;
			}
		}
	}
}

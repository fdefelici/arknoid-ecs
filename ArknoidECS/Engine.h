#ifndef ENGINE_H_
#define ENGINE_H_

#include "Costants.h"
#include "Components.h"

class World {

public:
	int next_entity() {
		for (int i = 0; i < MAX_ENTITY_NUM; i++) {
			if (this->masks[i] == 0) return i;
		}
		return -1;
	}

	bool has_component(int entity, int comp_mask) {
		if ((this->masks[entity] & comp_mask) == comp_mask) return true;
		else return false;
	}

public:
	unsigned long masks[MAX_ENTITY_NUM];
	float speeds[MAX_ENTITY_NUM];
	Transform transforms[MAX_ENTITY_NUM];
	RigidBody rbodies[MAX_ENTITY_NUM];
	BoxCollider colliders[MAX_ENTITY_NUM];
	SpriteRenderer sprites[MAX_ENTITY_NUM];
	HitResistance resistences[MAX_ENTITY_NUM];
	Sound sounds[MAX_ENTITY_NUM];
};


class Engine {

public:
	float deltaTime;
	sf::RenderWindow* window;
};



#endif ENGINE_H_

#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include "Costants.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

struct Sound {
	std::string file;
	sf::SoundBuffer buffer;
	sf::Sound audio;
};

struct Transform {
	sf::Vector2f position;
};


struct RigidBody {
	sf::Vector2f velocity;
	bool isKinematic;
};

struct HitResistance {
	int hardiness;
	int hits;
};

struct BoxCollider {
	sf::Vector2f offset;
	sf::Vector2f extent;
	struct Collision {
		bool has_begun;
		bool is_ongoing;
		CollisionSide hitSide;
		sf::Vector2f penetration;
		float velocityRatio;
		int entity;
	} collision;
};

struct SpriteRenderer {
	sf::RectangleShape rect;
	sf::CircleShape circle;
};

#endif
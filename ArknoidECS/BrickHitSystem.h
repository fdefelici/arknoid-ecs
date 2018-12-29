#ifndef BRICKHITSYSTEM_H_
#define BRICKHITSYSTEM_H_
#include "AbstractSystem.h"
/*
#include "Engine.h"

class BrickHitSystem {

public:
	void execute(World* aWorld, Engine* engine);
};
*/

class BrickHitSystem : AbstractSystem {

public:
	void execute(World* aWorld, Engine* engine);
};
#endif

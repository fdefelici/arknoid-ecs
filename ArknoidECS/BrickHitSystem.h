#ifndef BRICKHITSYSTEM_H_
#define BRICKHITSYSTEM_H_
#include "AbstractSystem.h"

class BrickHitSystem : AbstractSystem {

public:
	void execute(World* aWorld, Engine* engine);
};
#endif

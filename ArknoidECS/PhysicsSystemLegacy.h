#ifndef PHYSICSSYSTEMLEGACY_H_
#define PHYSICSSYSTEMLEGACY_H_
#include "AbstractSystem.h"

/*
	Naive physics implementation for testing purpose
*/
class PhysicsSystemLegacy : AbstractSystem {

public:
	void execute(World* aWorld, Engine* engine);
};

#endif

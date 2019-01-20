#ifndef PHYSICSSYSTEM_H_
#define PHYSICSSYSTEM_H_
#include "AbstractSystem.h"

class PhysicsSystem : AbstractSystem {

public:
	void execute(World* aWorld, Engine* engine);
};

#endif

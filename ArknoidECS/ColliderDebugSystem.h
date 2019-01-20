#ifndef COLLIDERDEBUGSYSTEM_H_
#define COLLIDERDEBUGSYSTEM_H_
#include "AbstractSystem.h"

class ColliderDebugSystem : AbstractSystem {

public:
	void execute(World* aWorld, Engine* engine);
};

#endif

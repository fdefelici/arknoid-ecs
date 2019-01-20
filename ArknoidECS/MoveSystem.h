#ifndef MOVESYSTEM_H_
#define MOVESYSTEM_H_
#include "AbstractSystem.h"

class MoveSystem : AbstractSystem {

public:
	void execute(World* aWorld, Engine* engine);
};

#endif

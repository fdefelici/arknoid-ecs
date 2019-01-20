#ifndef RENDERSYSTEM_H_
#define RENDERSYSTEM_H_
#include "AbstractSystem.h"

class RenderSystem : AbstractSystem {

public:
	void execute(World* aWorld, Engine* engine);
};

#endif

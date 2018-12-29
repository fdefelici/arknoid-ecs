#ifndef ABSTRACTSYSTEM_H_
#define ABSTRACTSYSTEM_H_
#include "Engine.h"

class AbstractSystem {

public:
	virtual void execute(World* aWorld, Engine* engine) = 0;
};

#endif

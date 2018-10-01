#pragma once

#include "TypeDef.h"
#include "GameObject.h"
#include "GameState.h"
#include <vector>

class IEnvirement {
public:
	IEnvirement(){}
	virtual ~IEnvirement(){}
	virtual std::vector<LivingObject*> & getLivingObjects() = 0;
	virtual std::vector<NonLivingObject*> & getNonLivingObjects() = 0;
};

class IGameWorldView {
public:
	virtual bool registerNewLivingObject( LivingObject * ) = 0;
	virtual BE_ID generateNextId() = 0;
	virtual IEnvirement * getEnvirement( vector2d & pos ) = 0;
	virtual GameState & getGameState() = 0;
};
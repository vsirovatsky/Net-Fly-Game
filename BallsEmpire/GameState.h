#pragma once

#include "TypeDef.h"

class GameState
{
public:
	GameState(void);
	~GameState(void);

	void moveScreenBy( vector2d moveBy );
	vector2d & getMoveBy();
private:
	vector2d currentScreenPos;
};


#include "GameState.h"


GameState::GameState(void) : currentScreenPos(0,0)
{
}


GameState::~GameState(void)
{
}

void GameState::moveScreenBy( vector2d moveBy )
{
	currentScreenPos.x += moveBy.x;
	currentScreenPos.y += moveBy.y;
}

vector2d & GameState::getMoveBy()
{
	return currentScreenPos;
}
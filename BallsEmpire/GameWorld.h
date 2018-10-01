#pragma once

#include "IMain.h"
#include "IGameWorldView.h"
#include "GameObject.h"
#include "BallsObject.h"
#include "UserInputManager.h"

class BallEnvirement : public IEnvirement {
public:
	BallEnvirement(){}
	virtual ~BallEnvirement(){}
	virtual std::vector<LivingObject*> & getLivingObjects(){return livings;}
	virtual std::vector<NonLivingObject*> & getNonLivingObjects(){return nonLivings;}
	std::vector<LivingObject*> livings;
	std::vector<NonLivingObject*> nonLivings;
};

class GameWorld : public IUserInputNavigationListener, public IGameWorldView {
public:
	GameWorld( IMain * );
	~GameWorld();

	void iterate();

	// from IGameWorldView
	virtual bool registerNewLivingObject( LivingObject * );
	virtual BE_ID generateNextId();
	virtual IEnvirement * getEnvirement( vector2d & pos );
	virtual GameState & getGameState(){return gameState;};

	//from IUserInputNavigationListener
	virtual void notifyMoveScreen( int byX, int byY );
private:
	IMain * mainInterface;
	void generate();
	BE_ID counter;
	GameState gameState;
};
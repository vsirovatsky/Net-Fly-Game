#include "BallsObject.h"


Ball::Ball( BE_ID id, IGameWorldView * _worldView ) : LivingObject(id), worldView(_worldView), empireId(-1)
{
	birthTime = SYSTEMCORE->Timer_GetTime();
}

BallsQueen::BallsQueen( BE_ID id, IGameWorldView * _worldView ) : Ball(id, _worldView), storedFood(500), breededWorkers(0)
{
	sprite=new hgeSprite( SYSTEM->getTexture("mediab/particles.png"), 96, 64, 32, 32);
	sprite->SetColor(0xFFFFA000);
	sprite->SetHotSpot(16,16);
	sprite->SetZ(0.1f);
	prevBreedTime = birthTime;
	storedFood = 500;
}

BallsQueen::~BallsQueen()
{
	delete sprite;
}

void BallsQueen::iterate()
{
	BE_FLOAT currTime = SYSTEMCORE->Timer_GetTime();
	if ( currTime > (prevBreedTime + SYSTEMCORE->Random_Float(2, 4)) ) {
		prevBreedTime = currTime;
		breed();
	}
}

void BallsQueen::render()
{
	if ( isDead() )
		sprite->RenderEx( getPos().x, getPos().y, 0, 0.4f );
	else {
		std::stringstream ss;
		ss << "Food: " << storedFood << ", life: " << getHP();
		SYSTEM->printText( 5, 5, ss.str().c_str() );
		sprite->RenderEx( getPos().x + worldView->getGameState().getMoveBy().x, getPos().y + worldView->getGameState().getMoveBy().y, 0, 2 );
	}
}

void BallsQueen::breed()
{
	if ( isDead() )
		return;
	if ( storedFood < 100 )
		return;
	int decision = SYSTEMCORE->Random_Int(0, 4);
	if ( (decision < 3) || (breededWorkers < 2) || (storedFood < 200) ) {
		storedFood -= 100;
		BallWorker * w = new BallWorker( worldView->generateNextId(), worldView );
		w->setQueen( this );
		w->setEmpireId( getEmpireId() );
		w->setPos( getPos() );
		w->setHP( 500 );
		worldView->registerNewLivingObject( w );
		breededWorkers++;
	} else {
		storedFood -= 200;
		BallSoldier * w = new BallSoldier( worldView->generateNextId(), worldView );
		w->setQueen( this );
		w->setEmpireId( getEmpireId() );
		w->setPos( getPos() );
		w->setHP( 1500 );
		worldView->registerNewLivingObject( w );
	}
}

void BallsQueen::storeFood( BE_INT food )
{
	storedFood += food;
}



BallWorker::BallWorker( BE_ID id, IGameWorldView * _worldView ) : Ball(id, _worldView), queen(0), carriedFood(0), foodFound(false), speed(100)
{
	sprite=new hgeSprite( SYSTEM->getTexture("mediab/particles.png"), 96, 64, 32, 32);
	sprite->SetColor(0xFFFFA000);
	sprite->SetHotSpot(16,16);
	sprite->SetZ(0.9f);
	prevActionTime = birthTime;
}

BallWorker::~BallWorker()
{
	delete sprite;
}

void BallWorker::iterate()
{
	if ( isDead() )
		return;
	if ( foodFound ) {
		carringFood();
	} else {
		lookingForFood();
	}
	
}

void BallWorker::render()
{
	if ( isDead() )
		sprite->RenderEx( getPos().x + worldView->getGameState().getMoveBy().x, getPos().y + worldView->getGameState().getMoveBy().y, 0, 0.1f );
	else
		sprite->RenderEx( getPos().x + worldView->getGameState().getMoveBy().x, getPos().y + worldView->getGameState().getMoveBy().y, 0, 0.5 );
}

void BallWorker::setQueen( BallsQueen * _queen )
{
	queen = _queen;
}

void BallWorker::lookingForFood()
{
	IEnvirement * env = worldView->getEnvirement( getPos() );
	if ( !env->getNonLivingObjects().empty() ) {
		FoodObject * nearest = 0;
		BE_FLOAT minDist = 999999999.0f;
		for ( std::vector<NonLivingObject *>::iterator it = env->getNonLivingObjects().begin(); it != env->getNonLivingObjects().end(); ++it ) {
			if ((*it)->getType() != NONLIVING_FOOD)
				continue;
			BE_FLOAT dist = getPos().getDistance( (*it)->getPos() );
			if ( (dist < minDist) && (((FoodObject *)(*it))->getAmount() > 0) ) {
				minDist = dist;
				nearest = (FoodObject *)(*it);
			}
		}
		if ( nearest ) {
			foodObject = nearest;
			foodFound = true;
			delete env;
			return;
		}
	}
	delete env;
	BE_FLOAT currTime = SYSTEMCORE->Timer_GetTime();
	if ( currTime > (prevActionTime + 5) ) {
		prevActionTime = currTime;
		direction = SYSTEMCORE->Random_Int(0, 4);
	}
	float dt = SYSTEMCORE->Timer_GetDelta();
	float x = 0;
	float y = 0;
	switch (direction) {
	case 1:
		x = dt * speed;
		break;
	case 2:
		x = -dt * speed;
		break;
	case 3:
		y = dt * speed;
		break;
	case 4:
		y = -dt * speed;
		break;
	}
	movePos( vector2d( x, y ) );
}

void BallWorker::carringFood()
{
	float dt = SYSTEMCORE->Timer_GetDelta();
	float distMoved = dt * speed;
	if ( carriedFood > 0 ) {
		if ( getPos().getDistance( queen->getPos() ) < distMoved ) {
			setPos( queen->getPos() );
			queen->storeFood( carriedFood );
			carriedFood = 0;
			return;
		} else {
			BE_FLOAT distX = queen->getPos().x - getPos().x;
			BE_FLOAT distY = queen->getPos().y - getPos().y;
			movePos( vector2d( (distX / abs(distX + distY)) * distMoved, (distY / abs(distX + distY)) * distMoved ) );
			return;
		}
	} else {
		if ( getPos().getDistance( foodObject->getPos() ) < distMoved ) {
			setPos( foodObject->getPos() );
			carriedFood = foodObject->takeAmount( 10 );
			if ( carriedFood == 0 )
				goToSearchMode();
			return;
		} else {
			BE_FLOAT distX = foodObject->getPos().x - getPos().x;
			BE_FLOAT distY = foodObject->getPos().y - getPos().y;
			movePos( vector2d( (distX / abs(distX + distY)) * distMoved, (distY / abs(distX + distY)) * distMoved ) );
			return;
		}
	}
}

void BallWorker::goToSearchMode(){
	prevActionTime = SYSTEMCORE->Timer_GetTime();
	direction = SYSTEMCORE->Random_Int(0, 4);
	foodObject = 0;
	foodFound = false;
}



BallSoldier::BallSoldier( BE_ID id, IGameWorldView * _worldView ) : Ball(id, _worldView), queen(0), enemyObject(0), enemyFound(false), speed(120)
{
	sprite=new hgeSprite( SYSTEM->getTexture("mediab/particles.png"), 96, 64, 32, 32);
	sprite->SetColor(0xFFFFA000);
	sprite->SetHotSpot(16,16);
	sprite->SetZ(0.9f);
	prevActionTime = birthTime;
}

BallSoldier::~BallSoldier()
{
	delete sprite;
}

void BallSoldier::iterate()
{
	if ( isDead() )
		return;

	if ( enemyFound ) {
		figtingWithEnemy();
	} else {
		lookingForEnemy();
	}
}

void BallSoldier::render()
{
	if ( isDead() )
		sprite->RenderEx( getPos().x + worldView->getGameState().getMoveBy().x, getPos().y + worldView->getGameState().getMoveBy().y, 0, 0.2f );
	else
		sprite->RenderEx( getPos().x + worldView->getGameState().getMoveBy().x, getPos().y + worldView->getGameState().getMoveBy().y, 0, 1 );
}

void BallSoldier::setQueen( BallsQueen * _queen )
{
	queen = _queen;
}

void BallSoldier::lookingForEnemy()
{
	IEnvirement * env = worldView->getEnvirement( getPos() );
	if ( !env->getLivingObjects().empty() ) {
		LivingObject * topPriorityTarget = 0;
		BE_FLOAT minDist = 999999999.0f;
		for ( std::vector<LivingObject *>::iterator it = env->getLivingObjects().begin(); it != env->getLivingObjects().end(); ++it ) {
			if (((*it)->getType() < LIVING) || ((*it)->getType() > NONLIVING) || ((*it)->getId() == getId()))
				continue;
			if ( (*it)->getType() == LIVING_BALL )
				if ( ((Ball*)(*it))->getEmpireId() == getEmpireId() ) 
					continue; // Current Empire
			BE_FLOAT dist = getPos().getDistance( (*it)->getPos() );
			if ( (dist < minDist) && !((LivingObject *)(*it))->isDead() ) {
				minDist = dist;
				topPriorityTarget = (LivingObject *)(*it);
			}
		}
		if ( topPriorityTarget ) {
			enemyObject = topPriorityTarget;
			enemyFound = true;
			delete env;
			return;
		}
	}
	delete env;
	BE_FLOAT currTime = SYSTEMCORE->Timer_GetTime();
	if ( currTime > (prevActionTime + 5) ) {
		prevActionTime = currTime;
		direction = SYSTEMCORE->Random_Int(0, 4);
	}
	float dt = SYSTEMCORE->Timer_GetDelta();
	float x = 0;
	float y = 0;
	switch (direction) {
	case 1:
		x = dt * speed;
		break;
	case 2:
		x = -dt * speed;
		break;
	case 3:
		y = dt * speed;
		break;
	case 4:
		y = -dt * speed;
		break;
	}
	movePos( vector2d( x, y ) );
}

void BallSoldier::figtingWithEnemy()
{
	if ( enemyObject->isDead() ) {
		goToSearchMode();
		return;
	}
	float dt = SYSTEMCORE->Timer_GetDelta();
	float distMoved = dt * speed;
	if ( getPos().getDistance( enemyObject->getPos() ) < distMoved ) {
		setPos( enemyObject->getPos() );
	} else {
		BE_FLOAT distX = enemyObject->getPos().x - getPos().x;
		BE_FLOAT distY = enemyObject->getPos().y - getPos().y;
		movePos( vector2d( (distX / abs(distX + distY)) * distMoved, (distY / abs(distX + distY)) * distMoved ) );
	}
	if ( getPos().getDistance( enemyObject->getPos() ) < 10 ) {
		enemyObject->hit( 3 );
	}
	if ( enemyObject->isDead() )
		goToSearchMode();
}

void BallSoldier::goToSearchMode(){
	prevActionTime = SYSTEMCORE->Timer_GetTime();
	direction = SYSTEMCORE->Random_Int(0, 4);
	enemyObject = 0;
	enemyFound = false;
}
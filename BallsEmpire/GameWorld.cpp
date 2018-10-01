#include "GameWorld.h"

GameWorld::GameWorld( IMain * _mainInterface ) : mainInterface(_mainInterface), counter(0)
{
	generate();
}

GameWorld::~GameWorld()
{
}

void GameWorld::iterate()
{
}

void GameWorld::generate()
{
	SYSTEMCORE->Random_Seed();

	BallsQueen * obj1 = new BallsQueen( generateNextId(), this );
	obj1->setPos( vector2d(300, 300) );
	obj1->setEmpireId( 1 );
	obj1->setHP(5000);
	mainInterface->getLivingObjectsRegister()->put( obj1 );

	BallsQueen * obj2 = new BallsQueen( generateNextId(), this );
	obj2->setPos( vector2d(800, 800) );
	obj2->setEmpireId( 2 );
	obj2->setHP(5000);
	mainInterface->getLivingObjectsRegister()->put( obj2 );

	BallsQueen * obj3 = new BallsQueen( generateNextId(), this );
	obj3->setPos( vector2d(1000, 0) );
	obj3->setEmpireId( 3 );
	obj3->setHP(5000);
	mainInterface->getLivingObjectsRegister()->put( obj3 );

	/*BallWorker * obj2 = new BallWorker( generateNextId(), this );
	obj2->setQueen( obj1 );
	obj2->setPos( vector2d(100, 100) );
	obj2->setEmpireId( 1 );
	obj2->setHP(500);
	mainInterface->getLivingObjectsRegister()->put( obj2 );

	BallWorker * obj3 = new BallWorker( generateNextId(), this );
	obj3->setQueen( obj1 );
	obj3->setPos( vector2d(200, 200) );
	obj3->setEmpireId( 1 );
	obj3->setHP(500);
	mainInterface->getLivingObjectsRegister()->put( obj3 );*/

	FoodObject * f = 0;
	f = new FoodObject( generateNextId(), 1000 );
	f->setPos( vector2d(500, 500) );
	mainInterface->getNonLivingObjectsRegister()->put( f );
	f = new FoodObject( generateNextId(), 100 );
	f->setPos( vector2d(500, -500) );
	mainInterface->getNonLivingObjectsRegister()->put( f );
	f = new FoodObject( generateNextId(), 500 );
	f->setPos( vector2d(-500, 500) );
	mainInterface->getNonLivingObjectsRegister()->put( f );
	f = new FoodObject( generateNextId(), 10 );
	f->setPos( vector2d(-500, -500) );
	mainInterface->getNonLivingObjectsRegister()->put( f );
	f = new FoodObject( generateNextId(), 1000 );
	f->setPos( vector2d(800, 600) );
	mainInterface->getNonLivingObjectsRegister()->put( f );
	f = new FoodObject( generateNextId(), 1000 );
	f->setPos( vector2d(100, 400) );
	mainInterface->getNonLivingObjectsRegister()->put( f );
}

void GameWorld::notifyMoveScreen( int byX, int byY )
{
	if ( (byX==0) && (byY==0) ) 
		return;
	float dt=SYSTEMCORE->Timer_GetDelta();
	float speed = 500.0f;
	vector2d toMove = vector2d();
	if (byX > 0) 
		toMove.x = speed * dt;
	else if (byX < 0) 
		toMove.x = -speed * dt;
	if (byY > 0) 
		toMove.y = speed * dt;
	else if (byY < 0) 
		toMove.y = -speed * dt;
	gameState.moveScreenBy( toMove );
	//SYSTEM->moveScreenBy( toMove );
	//mainInterface->getLivingObjectsRegister()->moveAllBy( toMove );
	//mainInterface->getNonLivingObjectsRegister()->moveAllBy( toMove );
}

BE_ID GameWorld::generateNextId()
{
	++counter;
	return counter;
}

bool GameWorld::registerNewLivingObject( LivingObject * obj )
{
	mainInterface->getLivingObjectsRegister()->put( obj );
	return true;
}

IEnvirement * GameWorld::getEnvirement( vector2d & pos )
{
	//TODO: improve
	BallEnvirement * env = new BallEnvirement();
	mainInterface->getLivingObjectsRegister()->populateNearBy( env->livings, pos, 500 );
	mainInterface->getNonLivingObjectsRegister()->populateNearBy( env->nonLivings, pos, 500 );
	return env;
}
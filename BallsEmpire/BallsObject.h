#pragma once

#include "GameObject.h"
#include "IGameWorldView.h"

class Ball : public LivingObject {
public:
	Ball(  BE_ID id, IGameWorldView * );
	virtual ~Ball(){}
	virtual void iterate() = 0;
	virtual void render() = 0;
	virtual void setEmpireId( BE_ID _empireId ){ empireId = _empireId; }
	virtual BE_ID & getEmpireId(){return empireId;}
	virtual OBJECT_TYPE getType(){return LIVING_BALL;}
protected:
	IGameWorldView * worldView;
	BE_ID empireId;
	BE_FLOAT birthTime;
};

class BallsQueen : public Ball {
public:
	BallsQueen(  BE_ID id, IGameWorldView * );
	virtual ~BallsQueen();
	virtual void iterate();
	virtual void render();
	void storeFood( BE_INT );
	//virtual OBJECT_TYPE getType(){return LIVING_BALL_QUEEN;}
private:
	hgeSprite * sprite;
	void breed();
	BE_FLOAT prevBreedTime;
	BE_INT storedFood;
	BE_INT breededWorkers;
};

class BallWorker : public Ball {
public:
	BallWorker( BE_ID id, IGameWorldView * );
	virtual ~BallWorker();
	virtual void iterate();
	virtual void render();
	//virtual OBJECT_TYPE getType(){return LIVING_BALL_WORKER;}
	void setQueen( BallsQueen * );
private:
	hgeSprite * sprite;
	BallsQueen * queen;
	BE_FLOAT prevActionTime;
	BE_INT direction;
	BE_INT carriedFood;
	bool foodFound;
	FoodObject * foodObject;
	void lookingForFood();
	void carringFood();
	void goToSearchMode();
	BE_FLOAT speed;
};

class BallSoldier : public Ball {
public:
	BallSoldier( BE_ID id, IGameWorldView * );
	virtual ~BallSoldier();
	virtual void iterate();
	virtual void render();
	//virtual OBJECT_TYPE getType(){return LIVING_BALL_SOLDIER;}
	void setQueen( BallsQueen * );
private:
	hgeSprite * sprite;
	BallsQueen * queen;
	BE_FLOAT prevActionTime;
	BE_INT direction;
	bool enemyFound;
	LivingObject * enemyObject;
	void lookingForEnemy();
	void figtingWithEnemy();
	void goToSearchMode();
	BE_FLOAT speed;
};
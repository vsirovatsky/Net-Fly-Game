#pragma once

#include "System.h"

#define OBJECT_TYPE int
#define COMMON_OBJECT 0
#define LIVING 1
#define LIVING_BALL 2
#define LIVING_BALL_QUEEN 3
#define LIVING_BALL_WORKER 4
#define LIVING_BALL_SOLDIER 5
#define NONLIVING 1000
#define NONLIVING_FOOD 1001

class GameObject {
public:
	GameObject( BE_ID _id ) : id(_id) {}
	virtual ~GameObject(){}
	virtual void render() = 0;
	virtual void setPos( vector2d & _pos );
	virtual vector2d & getPos();
	virtual void movePos( vector2d & _moveBy );
	virtual OBJECT_TYPE getType(){return COMMON_OBJECT;}
	virtual BE_ID getId(){return id;}
private:
	vector2d pos;
	BE_ID id;
};


class LivingObject : public GameObject {
public:
	LivingObject( BE_ID id );
	virtual ~LivingObject();
	virtual void iterate();
	virtual void render();
	virtual OBJECT_TYPE getType(){return LIVING;}
	virtual BE_INT getHP(){return hp;}
	virtual void setHP( BE_INT _hp ){hp = _hp;}
	virtual void hit( BE_INT hitAm ){hp -= ((hp > hitAm)?hitAm:hp);}
	virtual bool isDead(){return (hp <= 0);}
private:
	hgeSprite * sprite;
protected:
	BE_INT hp;
};


class NonLivingObject : public GameObject {
public:
	NonLivingObject( BE_ID _id ) : GameObject(_id) {}
	virtual ~NonLivingObject(){}
	virtual void render(){}
	virtual OBJECT_TYPE getType(){return NONLIVING;}
protected:
	hgeSprite * sprite;
};

class FoodObject : public NonLivingObject {
public:
	FoodObject( BE_ID , BE_INT );
	virtual ~FoodObject();
	virtual OBJECT_TYPE getType(){return NONLIVING_FOOD;}
	BE_INT getAmount(){return amount;}
	BE_INT takeAmount( BE_INT amountDesired ){
		BE_INT result = 0;
		if ( amountDesired > amount ) {
			result = amount;
			amount = 0;
		} else {
			result = amountDesired;
			amount -= amountDesired;
		}
		return result;
	}
	virtual void render();
private:
	BE_INT amount;
	BE_FLOAT rotation;
};
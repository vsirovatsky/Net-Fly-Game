#pragma once

#include "GameObject.h"
#include <hash_map>
#include <vector>

class LivingObjectsRegister {
public:
	LivingObjectsRegister(){}
	~LivingObjectsRegister();

	void put( LivingObject * );
	void remove( BE_ID );
	LivingObject * get( BE_ID );
	void renderAll();
	void iterateAll();

	void moveAllBy( vector2d & moveBy );

	void populateNearBy( std::vector<LivingObject*> & container, vector2d center, BE_FLOAT dist );
private:
	std::hash_map<BE_ID, LivingObject *> objects;
};

class NonLivingObjectsRegister {
public:
	NonLivingObjectsRegister(){}
	~NonLivingObjectsRegister();

	void put( NonLivingObject * );
	void remove( BE_ID );
	NonLivingObject * get( BE_ID );
	void renderAll();

	void moveAllBy( vector2d & moveBy );

	void populateNearBy( std::vector<NonLivingObject*> & container, vector2d center,BE_FLOAT dist );
private:
	std::hash_map<BE_ID, NonLivingObject *> objects;
};
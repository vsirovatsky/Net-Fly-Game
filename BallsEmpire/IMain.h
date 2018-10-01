#pragma once

#include "System.h"
#include "GameObjectsManager.h"
#include "SoundManager.h"

class IMain {
public:
	virtual LivingObjectsRegister * getLivingObjectsRegister() = 0;
	virtual NonLivingObjectsRegister * getNonLivingObjectsRegister() = 0;
	virtual SoundManager * getSoundManager() = 0;
};
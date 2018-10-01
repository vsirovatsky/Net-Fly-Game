#pragma once

#include "SimpleClientTypeDefs.h"

namespace simpleclient {

class ISimpleSoundState
{
public:
	ISimpleSoundState(void){};
	virtual ~ISimpleSoundState(void){};
	virtual SIMPLE_FLOAT & getSoundVolume() = 0;
	virtual SIMPLE_FLOAT & getMusicVolume() = 0;
	virtual void setSoundVolume( SIMPLE_FLOAT & ) = 0;
	virtual void setMusicVolume( SIMPLE_FLOAT & ) = 0;
};

class SimpleSoundState : public ISimpleSoundState
{
public:
	SimpleSoundState(void);
	virtual ~SimpleSoundState(void);
	virtual SIMPLE_FLOAT & getSoundVolume();
	virtual SIMPLE_FLOAT & getMusicVolume();
	virtual void setSoundVolume( SIMPLE_FLOAT & );
	virtual void setMusicVolume( SIMPLE_FLOAT & );
private:
	SIMPLE_FLOAT soundVolume;
	SIMPLE_FLOAT musicVolume;
};

}
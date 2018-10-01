#pragma once

#include "SimpleNetMessages.h"

namespace simpleclient {

class ISimpleVideoState
{
public:
	ISimpleVideoState(void){}
	virtual ~ISimpleVideoState(void){}
	virtual void setStarted() = 0;
	virtual void setStoped() = 0;
	virtual bool isStarted() = 0;

	virtual void setIdentity( OBJECT_IDENTITY & ) = 0;
	virtual OBJECT_IDENTITY & getIdentity() = 0;
	virtual bool isIdentity() = 0;
};



class SimpleVideoState : public ISimpleVideoState
{
public:
	SimpleVideoState(void);
	virtual ~SimpleVideoState(void);
	virtual void setStarted();
	virtual void setStoped();
	virtual bool isStarted();

	virtual void setIdentity( OBJECT_IDENTITY & );
	virtual OBJECT_IDENTITY & getIdentity();
	virtual bool isIdentity();
private:
	bool started;
	OBJECT_IDENTITY userObjIdentity;
};

}
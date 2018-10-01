#pragma once

#include "Logger.h"
#include "SimpleNetMessages.h"

namespace simpleclient {

class ISimpleNetState
{
public:
	ISimpleNetState(void){};
	virtual ~ISimpleNetState(void){};
	virtual void setConnected() = 0;
	virtual void setDisconnected() = 0;
	virtual bool isConnected() = 0;

	virtual void setIdentity( OBJECT_IDENTITY & ) = 0;
	virtual OBJECT_IDENTITY & getIdentity() = 0;
	virtual bool isIdentity() = 0;
};

class SimpleNetState : public ISimpleNetState
{
public:
	SimpleNetState(void);
	virtual ~SimpleNetState(void);
	virtual void setConnected();
	virtual void setDisconnected();
	virtual bool isConnected();

	virtual void setIdentity( OBJECT_IDENTITY & );
	virtual OBJECT_IDENTITY & getIdentity();
	virtual bool isIdentity();
private:
	bool connected;
	OBJECT_IDENTITY userObjIdentity;
};

}
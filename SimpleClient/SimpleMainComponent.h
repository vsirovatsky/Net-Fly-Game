#pragma once

#include "ISimpleMainComponentPanel.h"
#include "ThreadWrapper.h"
#include "SimpleNetManager.h"
#include "SimpleClientContext.h"
#include "SimpleVideoManager.h"
#include "SimpleSoundManager.h"

namespace simpleclient {

class SimpleMainComponent : public common::thread, public ISimpleMainComponentPanel
{
public:
	SimpleMainComponent(void);
	virtual ~SimpleMainComponent(void);

	virtual void run();
	void activate();

	SimpleClientContext * context;

	//from ISimpleMainComponentPanel
	virtual communications::AbstractPostOffice * getPostOffice(){return postOffice;};
	virtual filesystem::FileSystemFacade * getFileSystem(){return ff;};
private:
	void populateContext( void );
private:
	communications::AbstractPostOffice * postOffice;

	filesystem::FileSystemFacade * ff;

	SimpleNetManager * netMan;
	SimpleSoundManager * soundMan;
};

}
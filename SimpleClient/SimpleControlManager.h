#pragma once
#include "IInputReceiver.h"
#include "SimpleInputStateSnapshot.h"
#include "SimpleMovementProcessor.h"
#include "ISimpleVideoManagerPanel.h"
#include "ISimpleMovementListener.h"

namespace simpleclient {

class SimpleControlManager
{
public:
	SimpleControlManager(void);
	~SimpleControlManager(void);

	void iterate();

	void setInputReceiver( videosystem::IInputReceiver * );
	void setSimpleVideoManagerPanel( ISimpleVideoManagerPanel * );
	void setSimpleMovementListener( ISimpleMovementListener * );
private:
	videosystem::IInputReceiver * inputReceiver;
	SimpleMovementProcessor * movementProcessor;
	ISimpleVideoManagerPanel * videoPanel;
	ISimpleMovementListener * movementListener;

	SimpleInputStateSnapshot * prevShot;

	bool movementRequest;
};

}
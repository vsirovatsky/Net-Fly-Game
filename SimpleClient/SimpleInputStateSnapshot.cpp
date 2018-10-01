#include "StdAfx.h"
#include "Logger.h"
#include "SimpleInputStateSnapshot.h"

using namespace simpleclient;

// 500 miliseconds delta tern delay
#define DELTA_TURN_TIME 500

SimpleInputStateSnapshot::SimpleInputStateSnapshot(  videosystem::IInputReceiver * inputReceiver )
{
	if ( !inputReceiver )
		return;
	time = GetCurrentTime();
	forward = inputReceiver->IsKeyDown( videosystem::VS_KEY_CODE::KEY_KEY_W );
	backward = inputReceiver->IsKeyDown( videosystem::VS_KEY_CODE::KEY_KEY_S );
	left = inputReceiver->IsKeyDown( videosystem::VS_KEY_CODE::KEY_KEY_A );
	right = inputReceiver->IsKeyDown( videosystem::VS_KEY_CODE::KEY_KEY_D );
}


SimpleInputStateSnapshot::~SimpleInputStateSnapshot(void)
{
}

bool SimpleInputStateSnapshot::isUpdateTo( SimpleInputStateSnapshot & other )
{
	if ( (other.forward != forward) || (other.backward != backward) || (other.left != left) || (other.right != right) )
		return true;
	if ( time > (other.time + DELTA_TURN_TIME) ) 
		return true;
	return false;
}
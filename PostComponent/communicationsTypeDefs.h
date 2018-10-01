#pragma once

#include <iostream>
#include <vector>

namespace communications {

#define PC_STRING std::string
#define PC_MESSAGE_TYPE unsigned char 

#define MESSAGE_TYPE_BLANK 0
#define MESSAGE_TYPE_TEXT 1

enum COMPONENT_IDS {
	COMMUNICATIONS_COMPONENT_ID = 0,
	MASTER_COMPONENT_ID,
	INPUT_COMPONENT_ID,
	NET_COMPONENT_ID,
	FILE_COMPONENT_ID,
	SOUND_COMPONENT_ID,
	VIDEO_COMPONENT_ID
};

}
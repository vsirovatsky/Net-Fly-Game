#pragma once

#include <iostream>

#define SS_STRING std::string
#define SS_ID std::string
#define SS_SOUND_ADDRESS std::string
#define SS_INT int
#define VOLUME_DEFAULT 0.5f

namespace soundsystem {

	struct SoundData {
	public:
		SoundData( SS_ID _id, SS_SOUND_ADDRESS _address ) : id(_id), address(_address), looped(false), track(false), volume(VOLUME_DEFAULT) {}
		SS_ID id;
		SS_SOUND_ADDRESS address;
		bool looped;
		bool track;
		float volume;
	};

	struct SoundData3D {
	public:
		SS_ID id;
		SS_SOUND_ADDRESS address;
		float x;
		float y;
		float z;
		bool looped;
		bool track;
		float minDis;
		float maxDis;
		float volume;
	};
}
#pragma once
#if !defined(__SoundSystem__)
#define __SoundSystem__

#include <stdio.h>
#include "irrKlang\irrKlang.h"

#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif

using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

class SoundSystem
{
private:
	ISoundEngine* engine;
	bool valid;
	bool musicPlaying;
	ISound * music;
public:
	SoundSystem(void);
	~SoundSystem(void);
	void MusicToggle();
	void MusicOn();
	void MusicOff();
	void playShot();
private:
	bool isValid();
};

#endif
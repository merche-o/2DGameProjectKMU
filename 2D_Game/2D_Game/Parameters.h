#pragma once
#include "SoundEngine.h"

class Parameters
{
public:
	bool music;
	bool keySettings;
	SoundEngine &sound;

public:
	Parameters(SoundEngine &_sound);
	~Parameters(void);
};


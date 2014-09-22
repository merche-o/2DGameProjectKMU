#pragma once

#include <list>
#include "SFML\Audio.hpp"

class SoundEngine
{
private:
	std::list<sf::Sound> sound;
	std::list<sf::Music> music;
	bool activeSound;
	bool activeMusic;

public:
	SoundEngine(void);
	~SoundEngine(void);
};


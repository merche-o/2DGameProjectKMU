#pragma once

#include <map>
#include "SFML\Audio.hpp"

class SoundEngine
{
public:
	std::map<std::string, sf::SoundBuffer> soundBuffer;
	std::map<std::string, sf::Sound> sound;
	sf::Music music;
	bool activeSound;
	bool activeMusic;

private:

public:
	SoundEngine(void);
	~SoundEngine(void);

	void playSound(sf::Sound &, bool);
	void playMusic(sf::Music & Music);
	void musicON();
	void musicOFF();
};


#include "SoundEngine.h"


SoundEngine::SoundEngine(void)
{
	music.openFromFile("../Ressources/Musics/119-under-the-ground.ogg");
	activeMusic = false;
}


SoundEngine::~SoundEngine(void)
{
}

void SoundEngine::playSound(sf::Sound & Sound, bool b)
{
  if (!b || (b && Sound.getStatus() != sf::Sound::Playing))
    Sound.play();
}

void SoundEngine::playMusic(sf::Music & Music)
{
	if (activeMusic == true)
	{
		Music.setLoop(true);
		Music.setVolume(20);
		Music.play();
	}
}

void SoundEngine::musicON()
{
	activeMusic = true;
}

void SoundEngine::musicOFF()
{
	activeMusic = false;
}
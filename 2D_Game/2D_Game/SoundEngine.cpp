// Marc

#include "SoundEngine.h"


SoundEngine::SoundEngine(void)
{
	// Musics List
	music.openFromFile("./Ressources/Musics/MusicBob.ogg");
	activeMusic = false;
	
	// Sounds List
	soundBuffer["jump"] = (sf::SoundBuffer());
	soundBuffer["jump"].loadFromFile("./Ressources/Musics/jump.wav");
	sound["jump"] = (sf::Sound());
	sound["jump"].setBuffer(soundBuffer["jump"]);

	soundBuffer["coin"] = (sf::SoundBuffer());
	soundBuffer["coin"].loadFromFile("./Ressources/Musics/coin.wav");
	sound["coin"] = (sf::Sound());
	sound["coin"].setBuffer(soundBuffer["coin"]);
	
	soundBuffer["hit"] = (sf::SoundBuffer());
	soundBuffer["hit"].loadFromFile("./Ressources/Musics/hit.wav");
	sound["hit"] = (sf::Sound());
	sound["hit"].setBuffer(soundBuffer["hit"]);
	
	soundBuffer["shoot"] = (sf::SoundBuffer());
	soundBuffer["shoot"].loadFromFile("./Ressources/Musics/shoot.wav");
	sound["shoot"] = (sf::Sound());
	sound["shoot"].setBuffer(soundBuffer["shoot"]);
}


SoundEngine::~SoundEngine(void)
{
}

void SoundEngine::playSound(sf::Sound & Sound, bool b)
{
	if (!b || (b && Sound.getStatus() != sf::Sound::Playing)) // True = Wait until the sound is finished before playing once again
		Sound.play();
}

void SoundEngine::playMusic(sf::Music & Music)
{
	if (activeMusic == true)
	{
		Music.setLoop(true);
		Music.setVolume(60);
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
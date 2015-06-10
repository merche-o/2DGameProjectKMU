// Marc

#include "SoundEngine.h"


SoundEngine::SoundEngine(void)
{
	// Musics List
	music.openFromFile("./Ressources/Musics/MusicBob.ogg");
	activeMusic = true;
	activeSound = true;
	
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
	
	soundBuffer["select"] = (sf::SoundBuffer());
	soundBuffer["select"].loadFromFile("./Ressources/Musics/select.wav");
	sound["select"] = (sf::Sound());
	sound["select"].setBuffer(soundBuffer["select"]);
	
	soundBuffer["scroll"] = (sf::SoundBuffer());
	soundBuffer["scroll"].loadFromFile("./Ressources/Musics/scroll.wav");
	sound["scroll"] = (sf::Sound());
	sound["scroll"].setBuffer(soundBuffer["scroll"]);
}


SoundEngine::~SoundEngine(void)
{
}

void SoundEngine::playSound(sf::Sound & Sound, bool b)
{
	if ((!b || (b && Sound.getStatus() != sf::Sound::Playing)) && activeSound) // True = Wait until the sound is finished before playing once again
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
	else
		Music.pause();
}

void SoundEngine::musicON()
{
	activeMusic = true;
	if (music.Stopped)
		music.play();
}

void SoundEngine::musicOFF()
{
	activeMusic = false;
	music.stop();
}


void SoundEngine::soundSwitch()
{
	if (activeSound)
	activeSound = false;
	else
		activeSound = true;
}
#include "SoundEngine.h"


SoundEngine::SoundEngine(void)
{
}


SoundEngine::~SoundEngine(void)
{
}

void SoundEngine::playSound(sf::Sound & Sound, bool b)
{
  if (!b || (b && Sound.getStatus() != sf::Sound::Playing))
    Sound.play();
}
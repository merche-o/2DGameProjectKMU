// Marc

#include "Spell.h"


Spell::Spell(float & X, float & Y)
	: px(X), py(Y)
{
	// List of spells relative to functions
	actionSpell[EXPLOSION] = &Spell::explosion;
	actionSpell[LASER] = &Spell::laser;

	sf::Vector2u vec;
	vec = texture.getSize();
	width = vec.x;
	height = vec.y;
	scaleX = 1.0;
	scaleY = 1.0;
	play = false;
}


Spell::~Spell(void)
{
}

void Spell::launch()
{
	if (play == false) // Take position of the player when launched
	{
		play = true;
		x = px + 16;
		y = py + 80;
	}
	else if (play == true) // Play the spell
	{
		(this->*(actionSpell[type]))();
		if (scaleX > 5.0)
		{
			scaleX = 1.0;
			scaleY = 1.0;
			play = false;
		}
	}
}

// Scaling of spell when launched
void Spell::explosion()
{
	scaleX += 0.1;
	scaleY += 0.1;
}

void Spell::laser()
{
	scaleX += 1.0;
}
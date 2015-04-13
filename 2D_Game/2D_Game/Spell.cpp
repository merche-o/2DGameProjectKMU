// Marc

#include "Spell.h"


Spell::Spell(float & X, float & Y)
	: px(X), py(Y)
{
	actionSpell[EXPLOSION] = &Spell::explosion;
	actionSpell[LASER] = &Spell::laser;

	type = LASER;

	texture.loadFromFile("./Ressources/Images/laser.png");

	sf::Vector2u vec;
	vec = texture.getSize();
	//width = vec.x;
	//height = vec.y;

	scaleX = 1.0;
	scaleY = 1.0;

	play = false;
	launched = false;
}


Spell::~Spell(void)
{
}

void Spell::launch()
{
	if (launched == true)
	{
		launched = false;
		play = true;
		x = px + 16;
		y = py + 16;
	}
	if (play == true)
	{
		(this->*(actionSpell[type]))();
		if (type == EXPLOSION && scaleX > 5.0)
		{
			scaleX = 1.0;
			scaleY = 1.0;
			play = false;
		}
		else if (type == LASER && scaleX > 20.0)
		{
			scaleX = 1.0;
			play = false;
		}
	}
}

void Spell::explosion()
{
	scaleX += 0.1;
	scaleY += 0.1;
}

void Spell::laser()
{
	scaleX += 1.0;
}
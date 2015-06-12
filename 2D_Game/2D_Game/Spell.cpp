// Joris

#include "Spell.h"


Spell::Spell(float & X, float & Y, e_spell_type spellType)
	: px(X), py(Y), type(spellType)
{
	sf::Vector2u vec;
	vec = texture.getSize();
	//width = vec.x;
	//height = vec.y;

	scaleX = 1.0;
	scaleY = 1.0;

	play = false;
	launched = false;
	updateSpell(spellType);
}


Spell::~Spell(void)
{
}

void Spell::updateSpell(e_spell_type spellType)
{
	type = spellType;
	actionSpell[EXPLOSION] = &Spell::explosion;
	actionSpell[LASER] = &Spell::laser;

	if (type == LASER)
		texture.loadFromFile("./Ressources/Images/laser.png");
	else if (type == EXPLOSION)
		texture.loadFromFile("./Ressources/Images/explosion.png");
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
		if (type == EXPLOSION && scaleX > 14.0)
		{
			scaleX = 1.0;
			scaleY = 1.0;
			play = false;
		}
		else if (type == LASER && scaleX > 70.0)
		{
			scaleX = 1.0;
			play = false;
		}
	}
}

void Spell::explosion()
{
	scaleX += 2;
	scaleY += 4;
}

void Spell::laser()
{
	scaleX += 5.0;
}
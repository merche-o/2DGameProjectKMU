#pragma once

#include <SFML/Graphics.hpp>
#include <map>


enum e_spell_type
{
	EXPLOSION,
	LASER
};

class Spell
{
public:
	float & px;
	float & py;
	float x;
	float y;
	e_spell_type type;
	std::map<e_spell_type, void(Spell:: *)()> actionSpell;
	sf::Texture texture;
	unsigned int width;
	unsigned int height;
	float scaleX;
	float scaleY;
	bool play;
	bool launched;

public:
	Spell(float & X, float & Y);
	~Spell(void);

	void launch();
	void explosion();
	void laser();
};


// Marc

#include "Display.h"
#include "Settings.h"
#include <iostream>

Display::Display(sf::RenderWindow & w)
	: win(w)
{
	font.loadFromFile("./Ressources/Text/04B_30__.ttf");
}


Display::~Display(void)
{
}

void Display::loadCircle(float x, float y, float radius, sf::Color color, int transparency)
{
	sf::CircleShape circle;

	circle.setRadius(radius);
	circle.setFillColor(sf::Color(color.r, color.g, color.b, transparency));
	circle.setPosition(x, y);
	win.draw(circle);
}

void Display::loadImage(float x, float y, sf::Texture & Texture, int transparency)
{
	sf::Sprite		Sprite;

	Sprite.setTexture(Texture);
	Sprite.setPosition(x, y);
	Sprite.setColor(sf::Color(255, 255, 255, transparency));
	win.draw(Sprite);
}

void Display::loadSprite(sf::Sprite Sprite)
{
	win.draw(Sprite);
}

void Display::loadUnit(AUnit* unit)
{
	sf::Sprite	Sprite;

	Sprite.setTexture(unit->texture);
	Sprite.setPosition(unit->x, unit->y/* + Settings::HEIGHT_INTERFACE*/);
	win.draw(Sprite);
	
	/*** Particles ***/
	for (int j = 0; j < unit->particles.size(); ++j)
	{
		unit->particles[j]->update();
		if (unit->particles[j]->transp == 0)
			unit->particles.erase(unit->particles.begin() + j);
		//loadImage(unit->particles[j]->x, unit->particles[j]->y/* + Settings::HEIGHT_INTERFACE*/, unit->particles[j]->texture, unit->particles[j]->transp);
		loadCircle(unit->particles[j]->x, unit->particles[j]->y/* + Settings::HEIGHT_INTERFACE*/, unit->particles[j]->radius, unit->particles[j]->color, unit->particles[j]->transp);
	}
}

void Display::loadHitUnit(AUnit* unit, bool b)
{
	sf::Sprite	Sprite;

	for (int i = 0; i < unit->particles.size(); ++i)
		unit->particles[i]->color = sf::Color(255, 0, 0);

	Sprite.setTexture(unit->texture);
	Sprite.setPosition(unit->x, unit->y/* + Settings::HEIGHT_INTERFACE*/);
	if (b == true)
		Sprite.setColor(sf::Color(255, 255, 255, 50));
	else
		Sprite.setColor(sf::Color(255, 255, 255, 255));
	win.draw(Sprite);

	/*** Particles ***/
	for (int j = 0; j < unit->particles.size(); ++j)
	{
		unit->particles[j]->update();
		if (unit->particles[j]->transp == 0)
			unit->particles.erase(unit->particles.begin() + j);
		//loadImage(unit->particles[j]->x, unit->particles[j]->y/* + Settings::HEIGHT_INTERFACE*/, unit->particles[j]->texture, unit->particles[j]->transp);
		loadCircle(unit->particles[j]->x, unit->particles[j]->y/* + Settings::HEIGHT_INTERFACE*/, unit->particles[j]->radius, unit->particles[j]->color, unit->particles[j]->transp);
	}
}

void Display::loadText(float x, float y, sf::Font font, std::string str, int size, int r, int g, int b)
{
	sf::Text text;

	text.setFont(font);
	text.setCharacterSize(size);
	text.setColor(sf::Color(r, g, b));
	text.setPosition(x, y);
	text.setString(str);
	win.draw(text);
}

void Display::RefreshWindow()
{
  win.display();
}
#include "Display.h"
#include <iostream>

Display::Display(sf::RenderWindow & w)
	: win(w)
{
}


Display::~Display(void)
{
}

void Display::loadImage(float x, float y, sf::Texture & Texture, int transparency)
{
	sf::Sprite		Sprite;

	Sprite.setTexture(Texture);
	Sprite.setPosition(x, y);
	Sprite.setColor(sf::Color(255, 255, 255, transparency));
	win.draw(Sprite);
}

void Display::loadUnit(float x, float y, AUnit* unit)
{
	sf::Sprite	Sprite;

	Sprite.setTexture(unit->texture);
	Sprite.setPosition(unit->x, unit->y);
	Sprite.setTextureRect(sf::IntRect(unit->width * unit->animFrame + (3 * unit->width * unit->act), unit->height * unit->dir, unit->width, unit->height));
	win.draw(Sprite);
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
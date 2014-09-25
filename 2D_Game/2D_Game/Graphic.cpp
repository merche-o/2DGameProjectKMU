#include "Graphic.h"


Graphic::Graphic(sf::RenderWindow & w, Map & m)
	: Display(w), win(w), map(m)
{
}


Graphic::~Graphic(void)
{
}

void Graphic::affMap()
{
	sf::Font font;
	font.loadFromFile("Arial.ttf");
	loadText(10, 10, font, "test test test test", 20, 200, 200, 200);
	//for (int i = 0; i < map.map.size(); ++i)
	//{
	//	for (int j = 0; j < map.map[std::make_pair()].size(); ++j)
	//	{

	//	}
	//}
}
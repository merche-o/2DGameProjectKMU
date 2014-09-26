#include "Graphic.h"
#include "Settings.h"

Graphic::Graphic(sf::RenderWindow & w, Map & m, std::vector<Player*> & p)
	: Display(w), win(w), map(m), player(p)
{
}


Graphic::~Graphic(void)
{
}

void Graphic::affMap()
{
	int height_map = Settings::HEIGHT / Settings::CASE_SIZE;
	int width_map = Settings::WIDTH / Settings::CASE_SIZE;

	sf::Texture wall;
	wall.loadFromFile("../Ressources/Images/Wall.png");
	
	for (int y = 0; y < height_map; ++y)
	{
		for (int x = 0; x < width_map; ++x)
		{
			if (map.map[std::make_pair(y, x)].type == WALL)
				loadImage(x * (float)Settings::CASE_SIZE, y * (float)Settings::CASE_SIZE, wall);
		}
	}
}

void Graphic::affPlayer()
{
	loadUnit(player[0]->x, player[0]->y, player[0]);
}
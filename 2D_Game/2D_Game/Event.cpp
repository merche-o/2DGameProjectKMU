#include "Event.h"


Event::Event(sf::Window & w, std::vector<Player*> & p)
	: win(w), player(p)
{
}


Event::~Event(void)
{
}

void Event::checkEvent()
{
	while (win.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
            win.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				win.close();
			else if (event.key.code == sf::Keyboard::Up)
				player[0]->y--;
			else if (event.key.code == sf::Keyboard::Down)
				player[0]->y++;
			else if (event.key.code == sf::Keyboard::Left)
				player[0]->x--;
			else if (event.key.code == sf::Keyboard::Right)
				player[0]->x++;
			else if (event.key.code == sf::Keyboard::Z)
				player[0]->y -= 5;
			else if (event.key.code == sf::Keyboard::S)
				player[0]->y += 5;
			else if (event.key.code == sf::Keyboard::Q)
				player[0]->x -= 5;
			else if (event.key.code == sf::Keyboard::D)
				player[0]->x += 5;
			else if (event.key.code == sf::Keyboard::Space)
				player[0]->x = 150;
		}
    }
}
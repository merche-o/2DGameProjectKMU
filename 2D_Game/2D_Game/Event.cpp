#include "Event.h"


Event::Event(sf::Window & Window)
	: window(Window)
{
}


Event::~Event(void)
{
}

void Event::checkEvent()
{
	while (window.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
            window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
		}
    }
}
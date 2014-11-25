#include "Event.h"


Event::Event(sf::Window & w, std::vector<Player*> & p)
	: win(w), player(p)
{
}


Event::~Event(void)
{
}

void Event::checkEvent(bool & pause)
{
	while (win.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
            win.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				pause = true;
			/*** SHOOT EVENTS ***/
			else if (event.key.code == sf::Keyboard::Up)
				player[0]->inputMap[Event::I_FIRE_UP] = true;
			else if (event.key.code == sf::Keyboard::Down)
				player[0]->inputMap[Event::I_FIRE_DOWN] = true;
			else if (event.key.code == sf::Keyboard::Left)
				player[0]->inputMap[Event::I_FIRE_LEFT] = true;
			else if (event.key.code == sf::Keyboard::Right)
				player[0]->inputMap[Event::I_FIRE_RIGHT] = true;
			/*** MOVE EVENTS ***/
			else if (event.key.code == sf::Keyboard::Z)
				player[0]->inputMap[Event::I_UP] = true;
			else if (event.key.code == sf::Keyboard::S)
				player[0]->inputMap[Event::I_DOWN] = true;
			else if (event.key.code == sf::Keyboard::Q)
			{
				player[0]->dir = LEFT;
				player[0]->inputMap[Event::I_LEFT] = true;
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				player[0]->dir = RIGHT;
				player[0]->inputMap[Event::I_RIGHT] = true;
			}
			else if (event.key.code == sf::Keyboard::Space)
				player[0]->inputMap[Event::I_BONUS] = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up)
				player[0]->inputMap[Event::I_FIRE_UP] = false;
			else if (event.key.code == sf::Keyboard::Down)
				player[0]->inputMap[Event::I_FIRE_DOWN] = false;
			else if (event.key.code == sf::Keyboard::Left)
				player[0]->inputMap[Event::I_FIRE_LEFT] = false;
			else if (event.key.code == sf::Keyboard::Right)
				player[0]->inputMap[Event::I_FIRE_RIGHT] = false;
			else if (event.key.code == sf::Keyboard::Z)
				player[0]->inputMap[Event::I_UP] = false;
			else if (event.key.code == sf::Keyboard::S)
				player[0]->inputMap[Event::I_DOWN] = false;
			else if (event.key.code == sf::Keyboard::Q)
				player[0]->inputMap[Event::I_LEFT] = false;
			else if (event.key.code == sf::Keyboard::D)
				player[0]->inputMap[Event::I_RIGHT] = false;
			else if (event.key.code == sf::Keyboard::Space)
				player[0]->inputMap[Event::I_BONUS] = false;
		}
    }
}

void Event::menuEvent(int & pos, bool & push, bool & refresh, bool pause)
{
	while (win.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
            win.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape && !pause)
				win.close();
			else if (event.key.code == sf::Keyboard::Escape && pause)
			{
				push = true;
				refresh = true;
			}
			else if (event.key.code == sf::Keyboard::Return)
			{
				push = true;
				refresh = true;
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				--pos;
				refresh = true;
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				++pos;
				refresh = true;
			}
		}
	}
}
// Marc

#include "Event.h"


Event::Event(sf::Window & w, std::vector<Player*> & p, bool &k)
	: win(w), player(p), keySettings(k)
{
	keySettings = false;
	quitPause = true;
}


Event::~Event(void)
{
}

void Event::checkEvent(bool & pause, focus_state & focus)
{
	while (win.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
            win.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (keySettings)
				alternateEventPressed(pause);
			else
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
				else if	(event.key.code == sf::Keyboard::W)
					player[0]->inputMap[Event::I_UP] = true;
				else if (event.key.code == sf::Keyboard::S)
					player[0]->inputMap[Event::I_DOWN] = true;
				else if (event.key.code == sf::Keyboard::A)
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
				else if (event.key.code == sf::Keyboard::Q)
					player[0]->inputMap[Event::I_SWAP] = true;
				else if (event.key.code == sf::Keyboard::Num1)
					player[0]->inputMap[Event::I_WEAPON_1] = true;
				else if (event.key.code == sf::Keyboard::Num2)
					player[0]->inputMap[Event::I_WEAPON_2] = true;
				else if (event.key.code == sf::Keyboard::Num3)
					player[0]->inputMap[Event::I_WEAPON_3] = true;
				else if (event.key.code == sf::Keyboard::Num4)
					player[0]->inputMap[Event::I_WEAPON_4] = true;
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (keySettings)
				alternateEventReleased(pause);
			else
			{
				if (event.key.code == sf::Keyboard::Up)
					player[0]->inputMap[Event::I_FIRE_UP] = false;
				else if (event.key.code == sf::Keyboard::Down)
					player[0]->inputMap[Event::I_FIRE_DOWN] = false;
				else if (event.key.code == sf::Keyboard::Left)
					player[0]->inputMap[Event::I_FIRE_LEFT] = false;
				else if (event.key.code == sf::Keyboard::Right)
					player[0]->inputMap[Event::I_FIRE_RIGHT] = false;
				else if (event.key.code == sf::Keyboard::W)
					player[0]->inputMap[Event::I_UP] = false;
				else if (event.key.code == sf::Keyboard::S)
					player[0]->inputMap[Event::I_DOWN] = false;
				else if (event.key.code == sf::Keyboard::A)
					player[0]->inputMap[Event::I_LEFT] = false;
				else if (event.key.code == sf::Keyboard::D)
					player[0]->inputMap[Event::I_RIGHT] = false;
				else if (event.key.code == sf::Keyboard::Space)
					player[0]->inputMap[Event::I_BONUS] = false;
				else if (event.key.code == sf::Keyboard::Q)
					player[0]->inputMap[Event::I_SWAP] = false;
				else if (event.key.code == sf::Keyboard::Num1)
					player[0]->inputMap[Event::I_WEAPON_1] = false;
				else if (event.key.code == sf::Keyboard::Num2)
					player[0]->inputMap[Event::I_WEAPON_2] = false;
				else if (event.key.code == sf::Keyboard::Num3)
					player[0]->inputMap[Event::I_WEAPON_3] = false;
				else if (event.key.code == sf::Keyboard::Num4)
					player[0]->inputMap[Event::I_WEAPON_4] = false;
			}
		}
		else if (event.type == sf::Event::GainedFocus && focus != focus_state::CHANGING_TO_DESKTOP_RESOLUTION)
			focus = GAINED;
		else if (event.type == sf::Event::LostFocus && focus != focus_state::CHANGING_TO_DESKTOP_RESOLUTION)
			focus = LOST;
    }
}

void Event::alternateEventPressed(bool &pause)
{
		if (event.key.code == sf::Keyboard::Escape)
				pause = true;
			/*** SHOOT EVENTS ***/
			else if (event.key.code == sf::Keyboard::W)
				player[0]->inputMap[Event::I_FIRE_UP] = true;
			else if (event.key.code == sf::Keyboard::S)
				player[0]->inputMap[Event::I_FIRE_DOWN] = true;
			else if (event.key.code == sf::Keyboard::A)
				player[0]->inputMap[Event::I_FIRE_LEFT] = true;
			else if (event.key.code == sf::Keyboard::D)
				player[0]->inputMap[Event::I_FIRE_RIGHT] = true;
			/*** MOVE EVENTS ***/
			else if (event.key.code == sf::Keyboard::Up)
				player[0]->inputMap[Event::I_UP] = true;
			else if (event.key.code == sf::Keyboard::Down)
				player[0]->inputMap[Event::I_DOWN] = true;
			else if (event.key.code == sf::Keyboard::Left)
			{
				player[0]->dir = LEFT;
				player[0]->inputMap[Event::I_LEFT] = true;
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				player[0]->dir = RIGHT;
				player[0]->inputMap[Event::I_RIGHT] = true;
			}
			else if (event.key.code == sf::Keyboard::Space)
				player[0]->inputMap[Event::I_BONUS] = true;
			else if (event.key.code == sf::Keyboard::Q)
				player[0]->inputMap[Event::I_SWAP] = true;
			else if (event.key.code == sf::Keyboard::Num1)
				player[0]->inputMap[Event::I_WEAPON_1] = true;
			else if (event.key.code == sf::Keyboard::Num2)
				player[0]->inputMap[Event::I_WEAPON_2] = true;
			else if (event.key.code == sf::Keyboard::Num3)
				player[0]->inputMap[Event::I_WEAPON_3] = true;
			else if (event.key.code == sf::Keyboard::Num4)
				player[0]->inputMap[Event::I_WEAPON_4] = true;
}

void Event::alternateEventReleased(bool &pause)
{
		if (event.key.code == sf::Keyboard::W)
				player[0]->inputMap[Event::I_FIRE_UP] = false;
			else if (event.key.code == sf::Keyboard::S)
				player[0]->inputMap[Event::I_FIRE_DOWN] = false;
			else if (event.key.code == sf::Keyboard::A)
				player[0]->inputMap[Event::I_FIRE_LEFT] = false;
			else if (event.key.code == sf::Keyboard::D)
				player[0]->inputMap[Event::I_FIRE_RIGHT] = false;
			else if (event.key.code == sf::Keyboard::Up)
				player[0]->inputMap[Event::I_UP] = false;
			else if (event.key.code == sf::Keyboard::Down)
				player[0]->inputMap[Event::I_DOWN] = false;
			else if (event.key.code == sf::Keyboard::Left)
				player[0]->inputMap[Event::I_LEFT] = false;
			else if (event.key.code == sf::Keyboard::Right)
				player[0]->inputMap[Event::I_RIGHT] = false;
			else if (event.key.code == sf::Keyboard::Space)
				player[0]->inputMap[Event::I_BONUS] = false;
			else if (event.key.code == sf::Keyboard::Q)
				player[0]->inputMap[Event::I_SWAP] = false;
			else if (event.key.code == sf::Keyboard::Num1)
				player[0]->inputMap[Event::I_WEAPON_1] = false;
			else if (event.key.code == sf::Keyboard::Num2)
				player[0]->inputMap[Event::I_WEAPON_2] = false;
			else if (event.key.code == sf::Keyboard::Num3)
				player[0]->inputMap[Event::I_WEAPON_3] = false;
			else if (event.key.code == sf::Keyboard::Num4)
				player[0]->inputMap[Event::I_WEAPON_4] = false;
}


void Event::menuEvent(int & pos, bool & push, bool & refresh, focus_state & focus,bool main, bool pause)
{
	while (win.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
            win.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape && !pause)
			{
				if (main)
				win.close();
				return;
			}
			else if (event.key.code == sf::Keyboard::Escape && pause)
			{
				//pause = false;
				quitPause = false;

				refresh = true;
			}
			else if (event.key.code == sf::Keyboard::Return)
			{
				push = true;
				refresh = true;
			}
			else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
			{
				--pos;
				refresh = true;
			}
			else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
			{
				++pos;
				refresh = true;
			}
		}
		else if (event.type == sf::Event::GainedFocus && focus != focus_state::CHANGING_TO_DESKTOP_RESOLUTION)
			focus = GAINED;
		else if (event.type == sf::Event::LostFocus && focus != focus_state::CHANGING_TO_DESKTOP_RESOLUTION)
			focus = LOST;
	}
}
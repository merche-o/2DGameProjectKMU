#pragma once

#include "Display.h"
#include "Event.h"
#include "TextMenu.h"
#include "Parameters.h"
#include <utility>
#include <vector>
#include <map>
#include <string>

class GameMenu : public Display
{
private:
	enum e_state
	{
		MAIN,
		SETTINGS,
		CREDITS,
		PAUSE,
		NONE
	};

public:
	sf::RenderWindow & win;
	Parameters & param;
	std::map<std::pair<e_state, int>, TextMenu*> textMenu;
	std::map<std::pair<e_state, int>, void(GameMenu:: *)()> actionMenu;
	std::map<std::pair<e_state, int>, TextMenu*> keyTextMenu;
	std::map<e_state, int> sizeKeyTextMenu;
	std::map<e_state, int> sizeTextMenu;
	e_state currentState;
	std::vector<e_state> beforeState;
	int posMenu;
	bool isPushed;
	Event & event;
	bool & start;
	bool & menu;
	bool refresh;

public:
	GameMenu(sf::RenderWindow & w, Event & e, Parameters &p, bool & s, bool & m);
	~GameMenu(void);

	void posInsideTheMenu();
	void run();
	void pause();
	void displayCurrentMenu();
	void displayPause();
	void menuSettings();
	void menuCredits();
	void menuPause();
	void menuReturn();
	void backToMenu();
	void menuPlay();
	void addTextMenu(e_state state, TextMenu * text);
	void addKeyTextMenu(e_state state, TextMenu * text, void(GameMenu:: *p)());
};


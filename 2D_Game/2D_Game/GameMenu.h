#pragma once

#include <Windows.h>
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
		HOWPLAY,
		CREDITS,
		HIGHSCORE,
		PAUSE,
		ENDGAME,
		NONE
	};
	
public:
	sf::RenderWindow & win;
	Ressources & ress;
	Parameters & param;
	std::vector<std::string> scoreTable;
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
	bool restart;
	bool isFullscreen;
	int refreshFullscreen;
	Event::focus_state & focus;

public:
	GameMenu(sf::RenderWindow & w, Ressources & r, Event & e, Parameters & p, bool & s, bool & m, Event::focus_state & focus);
	~GameMenu(void);

	void posInsideTheMenu();
	void menuHowPlay();
	void run();
	void endGame(int score, int enemies_kill);
	void pause();
	void displayCurrentMenu();
	void displayPause();
	void displayEndGame(int score, int enemies_kill);
	void menuSettings();
	void menuHighscore();
	void menuCredits();
	void menuPause();
	void menuReturn();
	void menuQuitGame();
	void menuEndGame();
	void menuMain();
	void menuRestart();
	void menuMuteMusic();
	void menuMute();
	void menuToogleFullscreen();
	void menuSwitchControl();
	void backToMenu();
	void menuPlay();
	void toogleFullscreen();
	void focusChanged();
	void addTextMenu(e_state state, TextMenu * text);
	void addKeyTextMenu(e_state state, TextMenu * text, void(GameMenu:: *p)());
	void getScore();
};


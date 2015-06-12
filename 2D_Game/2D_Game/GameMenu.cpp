//Marc
#include "GameMenu.h"
#include <iostream>
#include <fstream>
#include <string>

GameMenu::GameMenu(sf::RenderWindow & w, Ressources & r, Event & e, Parameters & p, bool & s, bool & m, Event::focus_state & _focus)
	: Display(w), win(w), ress(r), event(e), param(p), start(s), menu(m), focus(_focus)
{
	refresh = true;
	posMenu = 0;
	restart = false;
	isFullscreen = true;
	refreshFullscreen = 3;
	currentState = MAIN; // Begin main menu
	beforeState.push_back(NONE); // No previous page

	/*****	MENU *****/

	// Banniere in (100,0)
	addTextMenu(MAIN, new TextMenu(850, 330, "Weapon Fire", 32, 250, 120, 60));
	addTextMenu(MAIN, new TextMenu(850, 580, "Player Move", 32, 250, 120, 60));
	addTextMenu(MAIN, new TextMenu(850, 710, "Use Spell", 32, 250, 120, 60));

	addKeyTextMenu(MAIN, new TextMenu(200, 200, "Play", 48), &GameMenu::menuPlay);
	addKeyTextMenu(MAIN, new TextMenu(200, 300, "Settings", 48), &GameMenu::menuSettings);
	addKeyTextMenu(MAIN, new TextMenu(200, 400, "How to Play", 48), &GameMenu::menuHowPlay);
	addKeyTextMenu(MAIN, new TextMenu(200, 500, "Highscore", 48), &GameMenu::menuHighscore);
	addKeyTextMenu(MAIN, new TextMenu(200, 600, "Credits", 48), &GameMenu::menuCredits);
	addKeyTextMenu(MAIN, new TextMenu(200, 700, "Quit", 48), &GameMenu::menuReturn);
	
	addTextMenu(SETTINGS, new TextMenu(350, 0, "Settings", 96, 250, 60, 60));
	addKeyTextMenu(SETTINGS, new TextMenu(400, 400, "Mute music", 48), &GameMenu::menuMuteMusic);
	addKeyTextMenu(SETTINGS, new TextMenu(400, 475, "Mute every sounds", 48), &GameMenu::menuMute);
	addKeyTextMenu(SETTINGS, new TextMenu(400, 550, "Toogle Fullscreen", 48), &GameMenu::menuToogleFullscreen);
	addKeyTextMenu(SETTINGS, new TextMenu(400, 625, "Switch controls", 48), &GameMenu::menuSwitchControl);
	addKeyTextMenu(SETTINGS, new TextMenu(400, 695, "Back", 48), &GameMenu::menuReturn);

	addTextMenu(HOWPLAY, new TextMenu(350, 0, "How to Play", 80, 250, 60, 60));

	addTextMenu(HOWPLAY, new TextMenu(850 / 3, 330, "Weapon Fire", 32, 250, 120, 60));
	addTextMenu(HOWPLAY, new TextMenu(850 / 3, 580, "Player Move", 32, 250, 120, 60));
	addTextMenu(HOWPLAY, new TextMenu(850 / 3, 710, "Use Spell", 32, 250, 120, 60));
	addKeyTextMenu(HOWPLAY, new TextMenu(800, 600, "Back", 32), &GameMenu::menuReturn);

	addTextMenu(CREDITS, new TextMenu(350, 0, "Credits", 96, 250, 60, 60));
	addTextMenu(CREDITS, new TextMenu(300, 150, "President :\tClaude Comair", 32, 60, 250, 150));
	addTextMenu(CREDITS, new TextMenu(300, 225, "Instructor :\tDavid Ly", 32, 60, 250, 250));
	addTextMenu(CREDITS, new TextMenu(300, 300, "Producer & Engine Dev :\tOlivier", 32, 60, 250, 150));
	addTextMenu(CREDITS, new TextMenu(300, 375, "Graphic Dev & Menu Dev :\tMarc", 32, 60, 250, 250));
	addTextMenu(CREDITS, new TextMenu(300, 450, "Physic Dev & Logic Dev :\tJoris", 32, 60, 250, 150));
	addTextMenu(CREDITS, new TextMenu(300, 525, "IA Dev & Logic Dev :\tAxel", 32, 60, 250, 250));
	addKeyTextMenu(CREDITS, new TextMenu(400, 700, "Back", 32), &GameMenu::menuReturn);

	addTextMenu(PAUSE, new TextMenu(600, 300, "Pause", 48, 200, 200, 200));
	addKeyTextMenu(PAUSE, new TextMenu(600, 400, "Resume Game", 32), &GameMenu::menuPlay);
	addKeyTextMenu(PAUSE, new TextMenu(600, 450, "New game", 32), &GameMenu::menuRestart);
	addKeyTextMenu(PAUSE, new TextMenu(600, 500, "How to Play", 32), &GameMenu::menuHowPlay);
	addKeyTextMenu(PAUSE, new TextMenu(600, 550, "Settings", 32), &GameMenu::menuSettings);
	addKeyTextMenu(PAUSE, new TextMenu(600, 600, "Back to menu", 32), &GameMenu::menuReturn);
	addKeyTextMenu(PAUSE, new TextMenu(600, 650, "Quit Game", 32), &GameMenu::menuQuitGame);

	addTextMenu(HIGHSCORE, new TextMenu(350, 0, "Highscore", 96, 250, 60, 60));
	addKeyTextMenu(HIGHSCORE, new TextMenu(400, 650, "Back", 64), &GameMenu::menuReturn);

	addTextMenu(ENDGAME, new TextMenu(600, 300, "Game Over", 48, 200, 200, 200));
	addKeyTextMenu(ENDGAME, new TextMenu(600, 450, "New game", 32), &GameMenu::menuPlay);
	addKeyTextMenu(ENDGAME, new TextMenu(600, 500, "Back to main menu", 32), &GameMenu::menuReturn);

}


GameMenu::~GameMenu(void)
{
}

void GameMenu::posInsideTheMenu() // Loop the cursor in menu
{
	if (posMenu < 0)
		posMenu = sizeKeyTextMenu[currentState] - 1;
	else if (posMenu > sizeKeyTextMenu[currentState] - 1)
		posMenu = 0;
}

void GameMenu::run()
{
	if (refresh == true || refreshFullscreen > 0) // Refresh the screen only if necessary
	{
		if (event.quitPause == false )
		{
			event.quitPause = true;
			if (currentState == PAUSE)
			{	
				this->menuPlay();
				refresh = true;
				return;
			}
		}
		if (refreshFullscreen > 0)
			refreshFullscreen--;
		if (isPushed == true) // Enter Event
		{
			if (posMenu != sizeKeyTextMenu[currentState] - 1) // If action != Return/Back
				beforeState.push_back(currentState);
			(this->*(actionMenu[std::make_pair(currentState, posMenu)]))(); // Call KeyTextMenu function
			posMenu = 0; // Reset cursor to 0
			isPushed = false;
			if (start == true) // Play the game
			{
				refresh = true;
				return;
			}
		}
		posInsideTheMenu(); // Keep cursor inside the menu
		
		win.clear();
		displayCurrentMenu(); // Display texts
	
		win.display();
		refresh = false;
	}

	// Menu Event
	if (currentState == PAUSE)
		event.menuEvent(posMenu, isPushed, refresh, focus,true ,true);
	else if (currentState == MAIN)
		event.menuEvent(posMenu, isPushed, refresh, focus, true);
	else
		event.menuEvent(posMenu, isPushed, refresh, focus, false ,true);
	if (focus != Event::focus_state::NONE)
				focusChanged();
}

void GameMenu::focusChanged()
{
	if (focus == Event::focus_state::CHANGING_TO_DESKTOP_RESOLUTION)
	{
		focus = Event::focus_state::NONE;
	}
	else if (focus == Event::focus_state::GAINED)
	{
		win.setFramerateLimit(Settings::FOCUS_GAME_FRAMERATE);
		if (isFullscreen)
		{
			win.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), Settings::GAME_NAME, sf::Style::Fullscreen);
		}
		refreshFullscreen = 10;
	}
	else if (focus == Event::focus_state::LOST)
	{
		ShowWindow(win.getSystemHandle(), SW_MINIMIZE);
		if (isFullscreen)
		{
			win.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), Settings::GAME_NAME, sf::Style::Default);
			ShowWindow(win.getSystemHandle(), SW_MINIMIZE);
			focus = Event::focus_state::CHANGING_TO_DESKTOP_RESOLUTION;
		}
		win.setFramerateLimit(Settings::NO_FOCUS_GAME_FRAMERATE);
	}
	if (focus != Event::focus_state::CHANGING_TO_DESKTOP_RESOLUTION)
		focus = Event::focus_state::NONE;
}

void GameMenu::pause()
{
	if (refresh == true)
	{
		if (isPushed == true)
		{
			if (posMenu != sizeKeyTextMenu[currentState] - 1) // If action != Return/Back
				beforeState.push_back(currentState);
			(this->*(actionMenu[std::make_pair(currentState, posMenu)]))(); // Call KeyTextMenu function
			posMenu = 0; // Reset cursor to 0
			isPushed = false;
			if (start == true) // Play the game
			{
				refresh = true;
				return;
			}
		}
		posInsideTheMenu();
		
		displayPause();
		win.display();

		refresh = false;
	}

	event.menuEvent(posMenu, isPushed, refresh, focus, true);
	if (focus != Event::focus_state::NONE)
				focusChanged();
}

void GameMenu::endGame(int score, int enemies_kill)
{
	if (refresh == true)
	{
		if (isPushed == true)
		{
			if (posMenu != sizeKeyTextMenu[currentState] - 1) // If action != Return/Back
				beforeState.push_back(currentState);
			(this->*(actionMenu[std::make_pair(currentState, posMenu)]))(); // Call KeyTextMenu function
			posMenu = 0; // Reset cursor to 0
			isPushed = false;
			if (start == true) // Play the game
			{
				refresh = true;
				return;
			}
		}
		posInsideTheMenu();
		win.clear();
		displayEndGame(score, enemies_kill);
		win.display();

		refresh = false;
	}

	event.menuEvent(posMenu, isPushed, refresh, focus, true);
	if (focus != Event::focus_state::NONE)
				focusChanged();
}

// Display Texts
void GameMenu::displayCurrentMenu()
{
	if (currentState == MAIN || currentState == HOWPLAY)
	{
		loadImage(850 / (currentState + 1), 160, ress.texture["arrow"]);
		loadImage(850 / (currentState + 1), 410, ress.texture["wasd"]);
		loadImage(850 / (currentState + 1), 660, ress.texture["space"]);
	}

	if (currentState == MAIN)
		loadImage(200, 10, ress.texture["title"]);

	for (int i = 0; i < sizeTextMenu[currentState]; ++i)
	{
		loadText(textMenu[std::make_pair(currentState, i)]->x, 
				textMenu[std::make_pair(currentState, i)]->y, 
				font, 
				textMenu[std::make_pair(currentState, i)]->text, 
				textMenu[std::make_pair(currentState, i)]->size,
				textMenu[std::make_pair(currentState, i)]->color.r, 
				textMenu[std::make_pair(currentState, i)]->color.g, 
				textMenu[std::make_pair(currentState, i)]->color.b);
	}

	for (int i = 0; i < sizeKeyTextMenu[currentState]; ++i)
	{
		if (posMenu == i) // Change color on cursor
		{
			loadText(keyTextMenu[std::make_pair(currentState, i)]->x, 
					keyTextMenu[std::make_pair(currentState, i)]->y, 
					font, 
					keyTextMenu[std::make_pair(currentState, i)]->text, 
					keyTextMenu[std::make_pair(currentState, i)]->size, 
					250, 250, 60);
		}
		else
		{
			loadText(keyTextMenu[std::make_pair(currentState, i)]->x, 
					keyTextMenu[std::make_pair(currentState, i)]->y, 
					font, 
					keyTextMenu[std::make_pair(currentState, i)]->text, 
					keyTextMenu[std::make_pair(currentState, i)]->size, 
					250, 150, 60);
		}
	}
	if (currentState == HIGHSCORE)
	{
		loadText(400, 150, font, "1 : " + scoreTable[0], 48, 60, 250, 250);
		loadText(400, 250, font, "2 : " + scoreTable[1], 48, 60, 250, 250);
		loadText(400, 350, font, "3 : " + scoreTable[2], 48, 60, 250, 250);
		loadText(400, 450, font, "4 : " + scoreTable[3], 48, 60, 250, 250);
		loadText(400, 550, font, "5 : " + scoreTable[4], 48, 60, 250, 250);
	}
	if (currentState == SETTINGS)
	{
		if (param.sound.activeMusic == true)
			loadText(400, 200, font, "Music : ON", 48, 60, 250, 250);
		else
			loadText(400, 200, font, "Music : OFF", 48, 60, 250, 250);
		if (param.sound.activeSound == true)
			loadText(400, 250, font, "Sound : ON", 48, 60, 250, 250);
		else
			loadText(400, 250, font, "Sound : OFF", 48, 60, 250, 250);
		if (param.keySettings == true)
			loadText(400,300, font, "Key Switched : ON", 48, 60, 250, 250);
		else
			loadText(400,300, font, "Key Switched : OFF", 48, 60, 250, 250);
	}
}

void GameMenu::displayPause()
{
	for (int i = 0; i < sizeTextMenu[currentState]; ++i)
	{
		loadText(textMenu[std::make_pair(currentState, i)]->x, 
				textMenu[std::make_pair(currentState, i)]->y, 
				font, 
				textMenu[std::make_pair(currentState, i)]->text, 
				textMenu[std::make_pair(currentState, i)]->size,
				textMenu[std::make_pair(currentState, i)]->color.r, 
				textMenu[std::make_pair(currentState, i)]->color.g, 
				textMenu[std::make_pair(currentState, i)]->color.b);
	}

	for (int i = 0; i < sizeKeyTextMenu[currentState]; ++i)
	{
		if (posMenu == i) // Change color on cursor
		{
			loadText(keyTextMenu[std::make_pair(currentState, i)]->x, 
					keyTextMenu[std::make_pair(currentState, i)]->y, 
					font, 
					keyTextMenu[std::make_pair(currentState, i)]->text, 
					keyTextMenu[std::make_pair(currentState, i)]->size, 
					250, 250, 60);
		}
		else
		{
			loadText(keyTextMenu[std::make_pair(currentState, i)]->x, 
					keyTextMenu[std::make_pair(currentState, i)]->y, 
					font, 
					keyTextMenu[std::make_pair(currentState, i)]->text, 
					keyTextMenu[std::make_pair(currentState, i)]->size, 
					250, 150, 60);
		}
	}
}

void GameMenu::displayEndGame(int score, int enemies_kill)
{
	for (int i = 0; i < sizeTextMenu[currentState]; ++i)
	{
		loadText(textMenu[std::make_pair(currentState, i)]->x, 
				textMenu[std::make_pair(currentState, i)]->y, 
				font, 
				textMenu[std::make_pair(currentState, i)]->text, 
				textMenu[std::make_pair(currentState, i)]->size,
				textMenu[std::make_pair(currentState, i)]->color.r, 
				textMenu[std::make_pair(currentState, i)]->color.g, 
				textMenu[std::make_pair(currentState, i)]->color.b);
	}

	for (int i = 0; i < sizeKeyTextMenu[currentState]; ++i)
	{
		if (posMenu == i) // Change color on cursor
		{
			loadText(keyTextMenu[std::make_pair(currentState, i)]->x, 
					keyTextMenu[std::make_pair(currentState, i)]->y, 
					font, 
					keyTextMenu[std::make_pair(currentState, i)]->text, 
					keyTextMenu[std::make_pair(currentState, i)]->size, 
					250, 250, 60);
		}
		else
		{
			loadText(keyTextMenu[std::make_pair(currentState, i)]->x, 
					keyTextMenu[std::make_pair(currentState, i)]->y, 
					font, 
					keyTextMenu[std::make_pair(currentState, i)]->text, 
					keyTextMenu[std::make_pair(currentState, i)]->size, 
					250, 150, 60);
		}
	}
	if (currentState == ENDGAME)
	{	
		loadText(600, 350, font, "Your score :" + std::to_string((long double)score), 48, 200, 200, 200);
		loadText(100, 300, font, "You killed", 48, 200, 200, 200);
		loadText(100, 350, font,std::to_string((long double)enemies_kill) + " enemies ", 48, 200, 200, 200);
	}
}



// Change state functions
void GameMenu::menuHowPlay()
{
	currentState = HOWPLAY;
}

void GameMenu::menuHighscore()
{
	
	currentState = HIGHSCORE;
}

void GameMenu::menuMain()
{
	currentState = MAIN;
}

void GameMenu::menuCredits()
{
	currentState = CREDITS;
}

void GameMenu::menuSettings()
{
	currentState = SETTINGS;
}

void GameMenu::menuPause()
{
	currentState = PAUSE;
}

void GameMenu::menuEndGame()
{
	currentState = ENDGAME;
}

void GameMenu::menuMuteMusic()
{
	currentState = beforeState[beforeState.size() - 1];
	beforeState.erase(beforeState.begin() + beforeState.size() - 1);
	if (param.sound.activeSound == false)
		return;
	if (param.sound.activeMusic)
		param.sound.musicOFF();
	else
		param.sound.musicON();
}

void GameMenu::menuMute()
{
	currentState = beforeState[beforeState.size() - 1];
	beforeState.erase(beforeState.begin() + beforeState.size() - 1);

	param.sound.soundSwitch();
		if (param.sound.activeSound)
		param.sound.musicON();
	else
		param.sound.musicOFF();
}


void GameMenu::menuSwitchControl()
{
	currentState = beforeState[beforeState.size() - 1];
	beforeState.erase(beforeState.begin() + beforeState.size() - 1);
	if (param.keySettings == true)
		param.keySettings = false;
	else
		param.keySettings = true;
}

void GameMenu::menuToogleFullscreen()
{
	currentState = beforeState[beforeState.size() - 1];
	beforeState.erase(beforeState.begin() + beforeState.size() - 1);
	toogleFullscreen();
}

// Back to previous menu
void GameMenu::menuReturn()
{

	if (beforeState[beforeState.size() - 1] == NONE || currentState == MAIN	) // Quit
		menuQuitGame();
	else
	{
		if (currentState == PAUSE ||currentState == ENDGAME)
		{
			menu = true;
			currentState = MAIN;
			beforeState.erase(beforeState.begin() + beforeState.size() - 1);
			refreshFullscreen = 3;
			return;

		}
		currentState = beforeState[beforeState.size() - 1];
		beforeState.erase(beforeState.begin() + beforeState.size() - 1);
		
	}
}

void GameMenu::menuQuitGame()
{
	currentState = beforeState[beforeState.size() - 1];
	beforeState.erase(beforeState.begin() + beforeState.size() - 1);
	win.close();
}

void GameMenu::backToMenu()
{	
	menu = true;
}

void GameMenu::menuPlay()
{
	start = true;
	if (beforeState.size() > 2 )
		{	
			currentState = MAIN;
			beforeState.erase(beforeState.begin() + beforeState.size() - 1);
		}
}

void GameMenu::menuRestart()
{
	restart = true;
	start = true;
	if (beforeState.size() > 2 )
		{	
			currentState = MAIN;
			beforeState.erase(beforeState.begin() + beforeState.size() - 1);
		}
}

void GameMenu::toogleFullscreen()
{
	if (isFullscreen)
		win.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), Settings::GAME_NAME, sf::Style::Default);
	else
	{
		win.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), Settings::GAME_NAME, sf::Style::Fullscreen);
		refreshFullscreen = 2;
	}
	isFullscreen = !isFullscreen;
}

// Simple texte
void GameMenu::addTextMenu(e_state state, TextMenu * text)
{
	textMenu[std::make_pair(state, sizeTextMenu[state])] = text;
	sizeTextMenu[state]++;
}

// Text linked to function
void GameMenu::addKeyTextMenu(e_state state, TextMenu * text, void(GameMenu:: *p)())
{
	keyTextMenu[std::make_pair(state, sizeKeyTextMenu[state])] = text;
	actionMenu[std::make_pair(state, sizeKeyTextMenu[state])] = p;
	sizeKeyTextMenu[state]++;
}

void GameMenu::getScore()
{
	int rank; char score[100];
	std::string fileName = "./Ressources/Highscore.txt";
	std::ifstream file(fileName.c_str(), std::ios::in);
	char line[256];
	bool firstline = true;
	if (file)
	{
		while(file.getline(line, 256))
		{
			if (firstline == true)
				firstline = false;
			else
			{
				int aNumb = sscanf_s(line, "%i:%s",&rank,&score);
				scoreTable.push_back(score);
			}
		}
		file.close();
	}
}

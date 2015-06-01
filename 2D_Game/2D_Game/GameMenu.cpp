//Marc
#include "GameMenu.h"
#include <iostream>
#include <fstream>
#include <string>

GameMenu::GameMenu(sf::RenderWindow & w, Event & e, Parameters & p, bool & s, bool & m)
	: Display(w), win(w), event(e), param(p), start(s), menu(m)
{
	refresh = true;
	posMenu = 0;
	restart = false;
	isFullscreen = true;
	refreshFullscreen = 2;
	currentState = MAIN; // Begin main menu
	beforeState.push_back(NONE); // No previous page

	/*****	MENU *****/
	addTextMenu(MAIN, new TextMenu(350, 0, "Menu", 96, 250, 60, 60));
	addKeyTextMenu(MAIN, new TextMenu(400, 200, "Play", 48), &GameMenu::menuPlay);
	addKeyTextMenu(MAIN, new TextMenu(400, 300, "Settings", 48), &GameMenu::menuSettings);
	addKeyTextMenu(MAIN, new TextMenu(400, 400, "How to Play", 48), &GameMenu::menuHowPlay);
	addKeyTextMenu(MAIN, new TextMenu(400, 500, "Highscore", 48), &GameMenu::menuHighscore);
	addKeyTextMenu(MAIN, new TextMenu(400, 600, "Credits", 48), &GameMenu::menuCredits);
	addKeyTextMenu(MAIN, new TextMenu(400, 700, "Quit", 48), &GameMenu::menuReturn);
	addTextMenu(SETTINGS, new TextMenu(350, 0, "Settings", 96, 250, 60, 60));
	addKeyTextMenu(SETTINGS, new TextMenu(400, 350, "Mute", 48), &GameMenu::menuMute);
	addKeyTextMenu(SETTINGS, new TextMenu(400, 450, "Toogle Fullscreen", 48), &GameMenu::menuToogleFullscreen);
	addKeyTextMenu(SETTINGS, new TextMenu(400, 600, "Back", 48), &GameMenu::menuReturn);

	addTextMenu(HOWPLAY, new TextMenu(350, 0, "How to Play", 80, 250, 60, 60));
	addTextMenu(HOWPLAY, new TextMenu(200, 200, "Q : Left", 32, 60, 250, 250));
	addTextMenu(HOWPLAY, new TextMenu(200, 300, "D : Right", 32, 60, 250, 250));
	addTextMenu(HOWPLAY, new TextMenu(200, 400, "Z : Jump", 32, 60, 250, 250));
	addTextMenu(HOWPLAY, new TextMenu(600, 200, "Left Arrow : Fire left", 32, 60, 250, 250));
	addTextMenu(HOWPLAY, new TextMenu(600, 300, "Right Arrow : Fire right", 32, 60, 250, 250));
	addTextMenu(HOWPLAY, new TextMenu(600, 400, "Up Arrow : Fire up", 32, 60, 250, 250));
	addTextMenu(HOWPLAY, new TextMenu(600, 500, "Space : Use spell", 32, 60, 250, 250));
	addKeyTextMenu(HOWPLAY, new TextMenu(400, 600, "Back", 32), &GameMenu::menuReturn);

	

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
	//addKeyTextMenu(PAUSE, new TextMenu(600, 650, "Quit Game", 32), &GameMenu::menuQuitGame);

	addTextMenu(HIGHSCORE, new TextMenu(350, 0, "Highscore", 96, 250, 60, 60));
	addKeyTextMenu(HIGHSCORE, new TextMenu(400, 650, "Back", 64), &GameMenu::menuReturn);

	addTextMenu(ENDGAME, new TextMenu(600, 300, "Game Over", 48, 200, 200, 200));
	addKeyTextMenu(ENDGAME, new TextMenu(600, 450, "New game", 32), &GameMenu::menuPlay);
	addKeyTextMenu(ENDGAME, new TextMenu(600, 500, "Back to main menu", 32), &GameMenu::menuReturn);

}


GameMenu::~GameMenu(void)
{
}

void GameMenu::posInsideTheMenu() // loop the cursor in menu
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
		
		if (currentState != PAUSE) // Do not clear the screen in Pause menu (we can see the game behind)
			win.clear();
		displayCurrentMenu(); // Display texts
		
		win.display();

		refresh = false;
	}
	// Menu Event
	if (currentState == PAUSE || currentState == ENDGAME)
		event.menuEvent(posMenu, isPushed, refresh, true);
	else
		event.menuEvent(posMenu, isPushed, refresh);
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

	event.menuEvent(posMenu, isPushed, refresh, true);
}

void GameMenu::endGame(int score)
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
		displayEndGame(score);
		win.display();

		refresh = false;
	}

	event.menuEvent(posMenu, isPushed, refresh, true);
}

// Display Texts
void GameMenu::displayCurrentMenu()
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
			loadText(400, 250, font, "music : ON", 48, 60, 250, 250);
		else
			loadText(400, 250, font, "music : OFF", 48, 60, 250, 250);
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

void GameMenu::displayEndGame(int score)
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
	//fix de merde
	if (currentState == ENDGAME)
		loadText(600, 350, font, "Your score :" + std::to_string((long double)score), 48, 200, 200, 200);
	if (currentState == HIGHSCORE) {
		loadText(400, 150, font, "1 : " + scoreTable[0], 64, 60, 250, 250);
		loadText(400, 250, font, "2 : " + scoreTable[1], 64, 60, 250, 250);
		loadText(400, 350, font, "3 : " + scoreTable[2], 64, 60, 250, 250);
		loadText(400, 450, font, "4 : " + scoreTable[3], 64, 60, 250, 250);
		loadText(400, 550, font, "5 : " + scoreTable[4], 64, 60, 250, 250);
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

void GameMenu::menuMute()
{
	currentState = beforeState[beforeState.size() - 1];
	beforeState.erase(beforeState.begin() + beforeState.size() - 1);
	if (param.sound.activeMusic)
		param.sound.musicOFF();
	else
		param.sound.musicON();
}

void GameMenu::menuToogleFullscreen()
{
	currentState = beforeState[beforeState.size() - 1];
	beforeState.erase(beforeState.begin() + beforeState.size() - 1);
	if (isFullscreen)
		win.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), Settings::GAME_NAME, sf::Style::Default);
	else
	{
		win.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), Settings::GAME_NAME, sf::Style::Fullscreen);
		refreshFullscreen = 1;
	}
	isFullscreen = !isFullscreen;
}

// Back to previous menu
void GameMenu::menuReturn()
{
	if (beforeState[beforeState.size() - 1] == NONE || currentState == MAIN	) // Quit
		menuQuitGame();
	else
	{
		if (currentState == PAUSE && beforeState[beforeState.size() -1] == MAIN)
		{
			menu = true;
		}
		currentState = beforeState[beforeState.size() - 1];
		beforeState.erase(beforeState.begin() + beforeState.size() - 1);
	}
}

void GameMenu::menuQuitGame()
{
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

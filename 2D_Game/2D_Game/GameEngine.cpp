// Marc

#include "GameEngine.h"
#include <iostream>
#include <fstream>

GameEngine::GameEngine(void)
	: ressources(),
		graphic(window, map, player, ennemyList, bulletList, itemList, ressources, loopTime),
		menu(window, event, parameters, restart, goMenu),
		sound(),
		map(loopTime),
		event(window, player),
		ref(ennemyList, itemList, bulletList, map, loopTime, ressources, sound),
		physics(player, ennemyList, itemList, bulletList, map, loopTime, sound),
		spawner(ennemyList, itemList, loopTime),
		IA(ref, ennemyList) 
{
	ressources.loadEnnemiesFromFile("./Ressources/Ennemies.txt");
	ressources.loadWeaponsFromFile("./Ressources/Weapons.txt");
	ressources.loadTextures();

	// Create window
	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME/*, sf::Style::Fullscreen*/);
	window.setFramerateLimit(30);

	physics._referee = &ref;
	
	player.push_back(new Player(ressources, loopTime, 0));
	
	state = MENU;
	restart = false;
	goMenu = false;
	pause = false;
	menu.getScore();
}


GameEngine::~GameEngine(void)
{
}

void GameEngine::writeScore()
{
	int i = 0;

	std::string fileName = "./Ressources/Highscore.txt";
	std::ofstream file(fileName.c_str(), std::ios::out | std::ios::trunc);
	std::string::size_type sz;
	bool write = true;
	file << "rank:score\n";

	while (i < 5)
	{
		if (std::stoi(this->menu.scoreTable[i], &sz) < this->player[0]->score && write == true)
		{
			this->menu.scoreTable[i] = std::to_string((long double)this->player[0]->score);
			write = false;
		}
		file << std::to_string((long double)i +1 ) << ":" << this->menu.scoreTable[i] << '\n';
		i++;
	}
	file.close();
}

void GameEngine::resetElement()
{
	ennemyList.clear();
	bulletList.clear();
	itemList.clear();
	player[0]->init(ressources);
	graphic.resetInterface();
	globalClock.restart();
	map.init(false);
}


void GameEngine::run()
{
    while (window.isOpen())
    {
		if (state == MENU)
		{
			menu.run();
			
			if (restart == true)
				state = GAME;
		}
		else if (state == GAME)
		{
			if (restart == true)
			{
				resetElement();
				restart = false;
				sound.musicON();
				sound.playMusic(sound.music);
			}
			
			window.clear();
	
			globalTimer = globalClock.getElapsedTime();
			loopTime = globalTimer.asSeconds();
			globalClock.restart();

			if (ref.dealDamage(player) == false)
			{
				writeScore();
				
				state = ENDGAME;
				goMenu = false;
				pause = false;
				menu.menuEndGame();
			}
			ref.cleanEnemyList();
			ref.cleanItemList();
			ref.moveBullet(player);
			spawner.spawnEnnemies(ressources.ennemy);
			spawner.spawnAmmo(player[0], ressources.texture["ammo"], &map);
			physics.playerAction(0);
			IA.setEnnemiesIM(player[0]->x, player[0]->y);
			physics.enemyAction();
			map.checkPlatform();
			
			player[0]->createParticles();
			
			if (player[0]->spell.launched == true || player[0]->spell.play == true)
				player[0]->spell.launch();
			
			/*** DISPLAY ***/
			graphic.affMap();
			graphic.affSpell();
			graphic.affUnits();
			graphic.affBullets();
			graphic.affItems();
			graphic.affInterface();

			if (state == GAME)
				event.checkEvent(pause);
		
			graphic.RefreshWindow();

			if (pause == true)
			{
				state = PAUSE;
				menu.menuPause();
			}
		}
		else if (state == PAUSE)
		{
			menu.run();
			//graphic.affPauseBG();
			if (goMenu == true)
			{

				resetElement();
				state = MENU;
				goMenu = false;
				pause = false;
			}
			if (restart == true)
			{
				pause = false;
				state = GAME;
				restart = false;
				globalClock.restart();
			}
		}
		else if (state == ENDGAME)
		{
			menu.endGame(player[0]->score);
			
			if (goMenu == true)
			{
				resetElement();
				state = MENU;
				menu.menuMain();
				goMenu = false;
				pause = false;
			}
			if (restart == true)
			{
				resetElement();
				pause = false;
				state = GAME;
				restart = false;
				globalClock.restart();
			}
		}
    }
}
// Marc

#include "GameEngine.h"
#include <iostream>
#include <fstream>

GameEngine::GameEngine(void)
	: ressources(),
		graphic(window, map, player, ennemyList, bulletList, itemList, ressources, loopTime),
		parameters(sound),
		menu(window, event, parameters, restart, goMenu),
		sound(),
		map(ressources, loopTime),
		event(window, player),
		ref(ennemyList, itemList, bulletList, map, loopTime, ressources, sound),
		physics(player, ennemyList, itemList, bulletList, map, loopTime, sound),
		spawner(ennemyList, itemList, loopTime),
		IA(ref, ennemyList) 
{
	// Create window
	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME/*, sf::Style::Fullscreen*/);
	window.setFramerateLimit(30);

	physics._referee = &ref;
	
	player.push_back(new Player(ressources, loopTime, 0));
	//have to put that on the event : touching new weapon
	player[0]->getNewWeapon(1,ressources);
	player[0]->getNewWeapon(2,ressources);
	player[0]->getNewWeapon(3,ressources);
	//player[0]->getNewWeapon(4,ressources);
	player[0]->numWeapon = 3;
	//
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

	FILE *fichier = NULL;
	std::string fileName = "./Ressources/Highscore.txt";

	fichier = fopen(fileName.c_str(),  "rwt");
	if (fichier == NULL)
	{
      printf("le fichier n'existe pas !");
	  std::ofstream file(fileName.c_str(), std::ios::out | std::ios::trunc);
	}

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
	//have to put that on the event : touching new weapon
	player[0]->getNewWeapon(1,ressources);
	player[0]->numWeapon += 1;
	//
	spawner.restart();
	graphic.resetInterface();
	globalClock.restart();
	ref.enemiesCount = 0;
	map.init(false);
}


void GameEngine::run()
{
    while (window.isOpen())
    {
		window.setMouseCursorVisible(false);
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
				//sound.musicON();
				//sound.musicOFF(); // For coding
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
			spawner.spawnEnnemies(ressources.ennemy, globalTimer);
			spawner.spawnAmmo(player[0], ressources.texture["ammo"], &map);
			map.checkPlatform();
			physics.playerAction(0);
			IA.setEnnemiesIM(player[0]);
			physics.enemyAction();
			//map.checkPlatform();
			
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
				sound.music.pause();
				state = PAUSE;
				menu.menuPause();
			}
		}
		else if (state == PAUSE)
		{
			//refesh l'affichage du jeux. pour pas avoir le bug cheloux de la pause
			if (menu.refresh == true)
			{
				graphic.affMap();
				graphic.affSpell();
				graphic.affUnits();
				graphic.affBullets();
				graphic.affItems();
				graphic.affPauseBG();
			}
			//graphic.affInterface();*/
		
			menu.run();
			
			if (goMenu == true)
			{
				resetElement();
				state = MENU;
				goMenu = false;
				pause = false;
			}

		if (restart == true)
			{
				if (menu.restart == true)
					{
						resetElement();
						menu.restart = false;
					}
				else if (sound.activeMusic)
					sound.music.play();
				pause = false;
				state = GAME;
				restart = false;
				globalClock.restart();
			}


		}
		else if (state == ENDGAME)
		{
			//std::cout << " Total Enemies = "<< ref.enemiesCount << std::cout;
			menu.endGame(player[0]->score);
			sound.musicOFF();
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
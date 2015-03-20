#pragma once

#include <vector>
#include <utility>
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Map.h"
#include "Event.h"
#include "Settings.h"
#include "Bullet.h"
#include "Coin.h"
#include "Ammo.h"
#include "SoundEngine.h"

class Referee
{
public:
	int colliderCheck(AUnit  *,  Event::Input const &);
	bool applyGravity(AUnit *);
	bool IAJumpToPlatform(AUnit *);
	void cleanEnemyList();
	void cleanItemList();
	void moveBullet(std::vector<Player *> &_player);
	bool dealDamage(std::vector<Player *> &_player);
	Referee(std::vector<AUnit*> & enemylist, std::vector<Item*> &itemList, std::vector<Bullet *> &bulletList, Map  &map, float &LoopTime, Ressources &Res, SoundEngine & sound);
	~Referee();
	
private:
	Map  &_map;
	Ressources &_res;
	SoundEngine &_sound;
	Player *tmp;
	float &loopTime;
	std::vector<AUnit*> & _enemyList;
	std::vector<Item*>  &_itemList;
	std::vector<Bullet*>  &_bulletList;
	void bulletHit(std::vector<Player *> &_player);
	//call collider in function of the collide Type (loop) 
	std::vector<int (Referee::  *)(AUnit  *, Event::Input const &)> collideManager;
	void dropCoins(Enemy *src);

	void playerInvinsibility(Player *player);

	//movement collide function that return wich 
	int collideWall(AUnit  *, Event::Input const &);
	int collideBonus(AUnit  *, Event::Input const &);
	int collideEnemy(AUnit  *, Event::Input const &);

	//
};


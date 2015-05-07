#pragma once

#include <map>
#include <vector>
#include <utility>
#include "Case.h"
#include "Platform.h"
#include "Trap.h"
#include "Ressources.h"

class Map
{
public:
	std::map<std::pair<int, int>, Case> map;
	std::vector<Platform*> platform;
	int number_platfoms;
	std::vector<Trap*> trap;

	float & loopTime;
	Ressources & ress;

private:

public:
	Map(Ressources & r, float & Time);
	void init(bool);
	~Map(void);

	void createPlatform(int x, int y, int length, bool symmetry = false);
	void checkPlatform();
	bool isRecyclable(int n);
	void rebuildPlatform();
};
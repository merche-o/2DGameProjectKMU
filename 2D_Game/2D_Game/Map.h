#pragma once

#include <map>
#include <vector>
#include <utility>
#include "Case.h"
#include "Platform.h"

class Map
{
public:
	std::map<std::pair<int, int>, Case> map;
	std::vector<Platform*> platform;

private:

public:
	Map(void);
	~Map(void);

	void createPlatform(int x, int y, int length, bool symmetry = false);
	void checkPlatform();
};
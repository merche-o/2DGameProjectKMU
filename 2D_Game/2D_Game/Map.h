#pragma once

#include <map>
#include <utility>
#include "Case.h"

class Map
{
private:
	std::map<std::pair<int, int>, Case> map;

public:
	Map(void);
	~Map(void);
};


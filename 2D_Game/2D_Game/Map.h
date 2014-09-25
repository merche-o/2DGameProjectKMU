#pragma once

#include <map>
#include <utility>
#include "Case.h"

class Map
{
public:
	std::map<std::pair<int, int>, Case> map;

private:

public:
	Map(void);
	~Map(void);
};
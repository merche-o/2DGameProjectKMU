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
	int number_platfoms;

	float & loopTime;

private:

public:
	Map(float & Time);
	void init(bool);
	~Map(void);

	void createPlatform(int x, int y, int length, bool symmetry = false);
	void checkPlatform();
	bool isRecyclable(int n);
	void rebuildPlatform();
};
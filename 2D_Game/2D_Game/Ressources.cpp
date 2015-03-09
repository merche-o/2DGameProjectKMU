// Marc

#include "Ressources.h"
#include <iostream>
#include <fstream>
#include <string>

Ressources::Ressources(void)
{
}


Ressources::~Ressources(void)
{
}

void Ressources::loadEnnemiesFromFile(std::string fileName)
{
	std::ifstream file(fileName.c_str(), std::ios::in);
	char line[256];

	if (file)
	{
		int p1, p2, p3, p4;
		char p5[100];
		std::string textureFile;
		bool firstLine = true;
        while(file.getline(line, 256)) // Read one line
        {
			if (firstLine == true)
				firstLine = false;
			else
			{
				int aNumb = sscanf_s(line, "%i:%i:%i:%i:%s", &p1, &p2, &p3, &p4, &p5, sizeof(p5)); // Get data
				textureFile.erase();
				textureFile = "./Ressources/Images/";
				textureFile += p5;
				float tmp = 0;
				ennemy.push_back(new AUnit(p1, p2, p3, p4, textureFile, tmp));			
			}
        }
		file.close();
	}
}

void Ressources::loadWeaponsFromFile(std::string fileName)
{
	std::ifstream file(fileName.c_str(), std::ios::in);
	char line[256];

	if (file)
	{
		int p1, p3, p4;
		float p2;
		bool firstLine = true;
        while(file.getline(line, 256)) // Read one line
        {
			if (firstLine == true)
				firstLine = false;
			else
			{
				int aNumb = sscanf_s(line, "%i:%f:%i:%i", &p1, &p2, &p3, &p4); // Get data
				
				weapon.push_back(new Weapon(p1, p2, p3, p4));
			}
        }
		file.close();
	}
}

void Ressources::loadTexturesFromFile(std::string fileName)
{
	// Map Texture
	texture["wall"].loadFromFile("./Ressources/Images/Wall.png");
	texture["coin"].loadFromFile("./Ressources/Images/ShieldBar.png");
	texture["ammo"].loadFromFile("./Ressources/Images/Ammo0.png");
}
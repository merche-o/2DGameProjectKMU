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
        while(file.getline(line, 256))
        {
			if (firstLine == true)
				firstLine = false;
			else
			{
				int aNumb = sscanf_s(line, "%i:%i:%i:%i:%s", &p1, &p2, &p3, &p4, &p5, sizeof(p5));
				textureFile.erase();
				textureFile = "../Ressources/Images/";
				textureFile += p5;
				ennemy.push_back(new AUnit(p1, p2, p3, p4, textureFile));
			}
        }
		file.close();
	}
}

void Ressources::loadWeaponsFromFile(std::string fileName)
{

}

void Ressources::loadTexturesFromFile(std::string fileName)
{
	// Map Texture
	texture["wall"].loadFromFile("../Ressources/Images/Wall.png");
}
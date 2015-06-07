// Marc

#include "Ressources.h"
#include <iostream>
#include <fstream>
#include <string>

Ressources::Ressources(void)
{
	loadEnnemiesFromFile("./Ressources/Ennemies.txt");
	loadWeaponsFromFile("./Ressources/Weapons.txt");
	loadTextures();
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

void Ressources::loadTextures()
{
	// Map Texture
	texture["Lplatform"].loadFromFile("./Ressources/Images/L_Platform.png");
	texture["Mplatform"].loadFromFile("./Ressources/Images/M_Platform.png");
	texture["Rplatform"].loadFromFile("./Ressources/Images/R_Platform.png");

	texture["LDplatform"].loadFromFile("./Ressources/Images/R_Dmg_Platform.png");
	texture["LDplatform"].loadFromFile("./Ressources/Images/R_Dmg_Platform.png");
	texture["LDplatform"].loadFromFile("./Ressources/Images/R_Dmg_Platform.png");
	
	//texture["htp_arrow"].loadFromFile("./Ressources/Images/htp_arrow.png");
	//texture["htp_space"].loadFromFile("./Ressources/Images/htp_space.png");
	//texture["htp_awd"].loadFromFile("./Ressources/Images/htp_awd.png");

	texture["coin"].loadFromFile("./Ressources/Images/coin.png");
	texture["life"].loadFromFile("./Ressources/Images/LifeBar.png");
	texture["shield"].loadFromFile("./Ressources/Images/ShieldBar.png");
	texture["ammo"].loadFromFile("./Ressources/Images/Ammo0.png");
	texture["interface"].loadFromFile("./Ressources/Images/Interface.png");
	texture["ammoLogo"].loadFromFile("./Ressources/Images/IAmmo.png");
	texture["ammoLogo1"].loadFromFile("./Ressources/Images/IAmmo1.png");
	texture["ammoLogo2"].loadFromFile("./Ressources/Images/IAmmo2.png");
	texture["ammoLogo3"].loadFromFile("./Ressources/Images/IAmmo3.png");
	texture["background"].loadFromFile("./Ressources/Images/BackgroundGame.png");
	texture["pause"].loadFromFile("./Ressources/Images/pause_bg.png");
	texture["weaponUsed"].loadFromFile("./Ressources/Images/weaponUsed.png");
	texture["arrow"].loadFromFile("./Ressources/Images/Arrow.png");
	texture["wasd"].loadFromFile("./Ressources/Images/wasd.png");
	texture["space"].loadFromFile("./Ressources/Images/Space.png");
}
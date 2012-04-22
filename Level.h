#pragma once

#include <vector>
#include <string>

#include "Planet.h"
#include "Entity.h"
#include "GoalZone.h"
#include "Weapon.h"

class Level 
{
	public:
		Level(const char* level_file_path);
		~Level();
		
		std::vector<Planet*> planets;
		Entity dude;
		Weapon weapon;
		GoalZone goalZone;
		std::string name;
		std::string description;
		
	private:
		std::vector<std::string> readFile(const char* path);
};

#include "Level.h"
#include "Vec2.h"

#include <fstream>
#include <string.h>

#define MAXLINES 1024
#define STRSIZE 8192

Level::Level(const char* level_file_path)
{
	std::vector<std::string> lines = readFile(level_file_path);

	float x, y, radius, mass, vx, vy, rotation, width, height, left, right, up, down;
	char* texture = (char*)malloc(STRSIZE*sizeof(char));
	char* yesno = (char*)malloc(10*sizeof(char));
	std::string namestring = "name: ";
	std::string descstring = "description: ";

	for(int i = 0; i < lines.size(); i++)
	{
		if(sscanf(lines[i].c_str(), "planet: %f %f %f %f %8192s", &x, &y, &radius, &mass, texture) == 5)
		{
			unsigned int texhandle = loadImage(texture);
			Planet* planet = new Planet(vec2(x, y), radius, mass, texhandle);
			planets.push_back(planet);
		}
		else if(sscanf(lines[i].c_str(), "entity: %f %f %f %f %f %f %f %f %f %8192s", &x, &y, &vx, &vy, &rotation, &radius, &mass, &width, &height, texture) == 10)
		{
			unsigned int texhandle = loadImage(texture);
			dude.setPBody(vec2(x, y), vec2(vx, vy), rotation, radius, mass);
			dude.setDBody(vec2(-width, height), vec2(width, -height), texhandle);
			weapon.init(&dude.physics_object);
		}
		else if(sscanf(lines[i].c_str(), "goalzone: %f %f %f %f %f %f\n", &x, &y, &left, &right, &up, &down) == 6)
		{
			goalZone.init(vec2(x, y), left, right, up, down);
		}			
		else if(lines[i].compare(0, namestring.length(), namestring) == 0)
		{
			name = lines[i];
		}
		else if(lines[i].compare(0, descstring.length(), descstring) == 0)
		{
			description = lines[i];
		}
	}
}

Level::~Level()
{

}

std::vector<std::string> Level::readFile(const char* path)
{
	std::vector<std::string> text_file;

	std::ifstream ifs(path);
	std::string temp;

	while(getline(ifs, temp))
		text_file.push_back(temp);
	
	return text_file;
}



#pragma once
//#include "Game.h"
#include <string>

using namespace std;

class Map
{
public:
	Map(string tID, int ms, int ts);
	~Map();

	void LoadMap(/*int arr[20][25]*/std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int x, int y);

	void LoadMapping(int arr[20][25]);
	void DrawMap();

private:
	std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;

	//SDL_Rect sRect, dRect;
	//SDL_Texture *dirt;
	//SDL_Texture *grass;
	//SDL_Texture *water;

	//int map[20][25];
};

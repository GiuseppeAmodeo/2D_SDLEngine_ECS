#include "pch.h"
#include "Map.h"
#include "Game.h"
//#include "TextureManager.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"

extern Manager manager;

//[row][column]
//0->water
//1->grass
//2->dirt
//
//int lvl1[20][25]
//{
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{1,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
//	{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
//};

Map::Map(string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;

	/*this->dirt = TextureManager::LoadTexture("Assets/dirt.png");
	this->grass = TextureManager::LoadTexture("Assets/grass.png");
	this->water = TextureManager::LoadTexture("Assets/water.png");
	LoadMapping(lvl1);
	sRect.x = sRect.y = 0;
	sRect.w = dRect.w = 32;
	sRect.h = dRect.h = 32;
	dRect.x = dRect.y = 0;*/
}

Map::~Map()
{
	//SDL_DestroyTexture(grass);
	//SDL_DestroyTexture(dirt);
	//SDL_DestroyTexture(water);
}

void Map::LoadMap(/*int arr[20][25]*/ std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			srcY = atoi(&tile) * tileSize;

			mapFile.get(tile);
			srcX = atoi(&tile) * tileSize;

			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);

			//Game::AddTile(atoi(&tile), x * 32, y * 32);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);

			if (tile == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize , scaledSize,0);
				tcol.addGroup(Game::groupColliders);
				//mapFile.ignore();
			}

			mapFile.ignore();
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xPos, int yPos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xPos, yPos, tileSize, mapScale, texID);
	tile.addGroup(Game::groupMap);
	//tile.addComponent<TileComponent>(x, y, 32, 32, id);
}

//void Map::LoadMapping(int arr[20][25])
//{
	/*for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			map[row][column] = arr[row][column];
		}
	}*/
//}

//void Map::DrawMap()
//{
	/*
	int type = 0;

	for (int row = 0; row < 20; row++)
	{
		for (int column = 0; column < 25; column++)
		{
			type = map[row][column];

			dRect.x = column * 32;
			dRect.y = row * 32;

			switch (type)
			{
			case 0:
				TextureManager::DrawMap(grass, sRect, dRect);
				break;
			case 1:
				TextureManager::DrawMap(dirt, sRect, dRect);
				break;
			case 2:
				TextureManager::DrawMap(water, sRect, dRect);
				break;
			default:
				break;
			}

		}
	}*/
//}
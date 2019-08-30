#pragma once

//#ifndef GAME_H
//#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "AssetManager.h"
#include "Test.h"

class AssetManager;
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void HandleEvents();
	void Update();
	void Renderer();
	void Clean();
	bool Running() { return isRunning; }

	//static void AddTile(int srcX,int srcY,int x, int y);
	static SDL_Renderer *renderer;
	static SDL_Event event;
	//static vector<ColliderComponent*> colliders;
	static bool isRunning;
	static SDL_Rect camera;

	static AssetManager* assets;

	enum  groupLabel : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectile,
		groupEnemies,
		groupBoxCollider2D,
	};

private:
	int cnt = 0;
	SDL_Window *window;
	//SDL_Renderer *renderer;

};

//#endif // !GAME_H


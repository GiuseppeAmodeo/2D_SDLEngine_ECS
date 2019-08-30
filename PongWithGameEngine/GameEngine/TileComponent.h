#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include <string>

using namespace std;


class TileComponent : public Component
{
public:
	//TransformComponent *transform;
	//SpriteComponent *sprite;

	//SDL_Rect tileRect;
	//int tileID;
	//const char *path;

	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, int tsize, int tscale, string id)
	{
		texture = Game::assets->GetTexture(id);

		position.x = xPos;
		position.y = yPos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tsize;

		destRect.x = xPos;
		destRect.y = yPos;
		destRect.w = destRect.h = tsize * tscale;
	}

	void Update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;

	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

	/*TileComponent(int x, int y, int w, int h, int id)
	{*/
	/*tileRect.x = x;
	tileRect.y = y;
	tileRect.w = w;
	tileRect.h = h;
	tileID = id;*/

	/*switch (tileID)
	{
	case 0:
		path = "Assets/grass.png";
		break;
	case 1:
		path = "Assets/dirt.png";
		break;
	case 2:
		path = "Assets/water.png";
		break;
	default:
		break;
	}*/
	//}

	/*void Init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();
		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}*/
};


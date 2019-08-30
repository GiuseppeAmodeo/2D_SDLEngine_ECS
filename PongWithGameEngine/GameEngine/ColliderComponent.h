#pragma once
#include <string>
#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"

using namespace std;

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	string tag;
	float offset;
	SDL_Texture *tex;
	SDL_Rect srcR, destR;

	TransformComponent *transform;

	ColliderComponent(string t)
	{
		tag = t;
	}

	ColliderComponent(string t, int xPos, int yPos, int size, float offset)
	{
		tag = t;
		collider.x = xPos;
		collider.y = yPos;
		this->offset = offset;
		collider.h = collider.w = size;
	}

	void Init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("Assets/ColTex.png");
		srcR = { 0,0,32,32 };
		destR = { collider.x, collider.y ,collider.w, collider.h + (int)offset };

		//Game::colliders.push_back(this);
	}

	void Update() override
	{
		if (tag != "terrain")
		{
			collider.x = (transform->position.x );
			collider.y = (transform->position.y  );
			collider.w = transform->width;
			collider.h = transform->height   * transform->scale;
		}

		destR.x = collider.x -Game::camera.x;
		destR.y = collider.y  -Game::camera.y;
	}

	void Draw() override
	{
		if (tag == "terrain")
		TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};

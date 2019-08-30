#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include <string>
#include "AssetManager.h"

using namespace std;


class SpriteComponent : public Component
{
private:
	TransformComponent *transform;
	TransformComponent transforms;

	SDL_Texture *texture;
	SDL_Rect sRect, dRect;
	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(string id)
	{
		SetTex(id);
		/*texture = TextureManager::LoadTexture(path);*/
	}

	SpriteComponent(string id,bool isAnimated)
	{
		//transform->position.x;

		animated = isAnimated;
		
		Animation idle = Animation(0,3,100);
		Animation walk = Animation(1, 8, 100);

		animations.emplace("Idle",idle);
		animations.emplace("Walk", walk);
 
	/*	frames = nFrames;
		speed = mSpeed;*/
		
		Play("Idle");

		SetTex(id);
		/*texture = TextureManager::LoadTexture(path);*/
	}

	~SpriteComponent()
	{
		//SDL_DestroyTexture(texture);
	}

	void SetTex(string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	void Init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		sRect.x = sRect.y = 0;
		sRect.w = transform->width;
		sRect.h = transform->height;
		//dRect.w = dRect.h = 64;
	}

	void Update() override
	{
		if (animated)
		{
			sRect.x = sRect.w*static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		sRect.y = animIndex * transform->height;

		dRect.x = static_cast<int>(transform->position.x);// -Game::camera.x;
		dRect.y = static_cast<int>(transform->position.y);// -Game::camera.y;
		dRect.w = transform->width  * transform->scale;
		dRect.h = transform->height * transform->scale;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, sRect, dRect,spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};


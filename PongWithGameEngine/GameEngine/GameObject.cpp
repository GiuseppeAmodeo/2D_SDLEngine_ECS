#include "pch.h"
#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char *textureSheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(textureSheet);

	xPos = x;
	yPos = y;

}

void GameObject::Update()
{
	xPos++;
	yPos++;

	sRect.h = 32;
	sRect.w = 50;
	sRect.x = 0;
	sRect.y = 0;

	dRect.x = xPos;
	dRect.y = yPos;
	dRect.w = sRect.w * 2;
	dRect.h = sRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &sRect, &dRect);

}	
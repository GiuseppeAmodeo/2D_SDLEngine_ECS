#include "pch.h"
#include "TextureManager.h"

SDL_Texture *TextureManager::LoadTexture(const char * fileName)
{
	SDL_Surface *tmpSurface = IMG_Load(fileName);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}

void TextureManager::Draw(SDL_Texture * tex, SDL_Rect sRect, SDL_Rect dRect, SDL_RendererFlip spriteFlip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &sRect, &dRect,NULL,NULL,spriteFlip);
}

void TextureManager::DrawMap(SDL_Texture * tex, SDL_Rect sRect, SDL_Rect dRect)
{
	SDL_RenderCopy(Game::renderer, tex, &sRect, &dRect);
}
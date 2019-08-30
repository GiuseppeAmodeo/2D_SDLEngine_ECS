#include "pch.h"
#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range,int speed, string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x,pos.y,32,32,1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed,vel);
	projectile.addComponent<ColliderComponent>("projectile",projectile.getComponent<TransformComponent>().position.x, projectile.getComponent<TransformComponent>().position.y,21,0);
	projectile.addGroup(Game::groupProjectile);
}

void AssetManager::CreateBall(Vector2D pos, Vector2D vel, int speed, string id)
{
	auto& ball(manager->addEntity());
	ball.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	ball.addComponent<SpriteComponent>(id, false);
	ball.addComponent<BallComponent>(speed,vel);
	ball.addComponent<ColliderComponent>("Ball", ball.getComponent<TransformComponent>().position.x, ball.getComponent<TransformComponent>().position.y, 21, 21);
	ball.addGroup(Game::groupProjectile);
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id,TTF_OpenFont(path.c_str(),fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}
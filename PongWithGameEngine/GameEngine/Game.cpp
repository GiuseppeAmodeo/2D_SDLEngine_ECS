//#include "GameObject.h"
//#include "ECS.h"

#include "pch.h"
#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include <iostream>
#include <typeinfo>
#include "AssetManager.h"
#include <sstream>
#include "SDL_ttf.h"

//using namespace std;

//SDL_Texture *playerTexture;
//SDL_Rect sRect, destRect;
//GameObject *player;
//GameObject *enemy;

const int BALL_X = 390;
const int BALL_Y = 290;

Map* mMap;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera{ 0,0,800,600 };

//vector<ColliderComponent*> Game::colliders;
AssetManager *Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

auto& player(manager.addEntity());

auto& enemy(manager.addEntity());

auto& boxCollider2D_Up(manager.addEntity());
auto& boxCollider2D_Down(manager.addEntity());
auto& playerLabel(manager.addEntity());
auto& enemyLabel(manager.addEntity());

int xvel, yvel;
int playerScore, enemyScore;

//auto& wall(manager.addEntity());

//auto& water(manager.addEntity());

//auto& tile0(manager.addEntity());    //WATER TILE.
//auto& tile1(manager.addEntity());   //GRASS  TILE
//auto& tile2(manager.addEntity());  //WALL    TILE

//const char* mapFile = "Assets/terrain_ss.png";

//auto& tiles(manager.getGroup(groupMap));
//auto& players(manager.getGroup(groupPlayers));
//auto& enemies(manager.getGroup(groupEnemies));

Game::Game()
{

}

Game::~Game()
{

}

int GetRandomNumber(int min, int max)
{
	srand(time(NULL));
	return rand() % max + min;
}

void Game::Init(const char *title, int xpos, int ypos, int widht, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	else
	{
		flags = SDL_WINDOW_SHOWN;
	}

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		cout << "Subsystems Initialised\n";
		window = SDL_CreateWindow(title, xpos, ypos, widht, height, flags);

		if (window)
		{
			cout << "Window Created!\n";
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			cout << "Renderer created!\n";
		}

		isRunning = true;
	}

	else
	{
		isRunning = false;
	}

#pragma region  Comment
	//SDL_Surface *tmpSurface = IMG_Load("Assets/SuperMario.png"); //create a surface that contain this texture.
	//playerTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface); //crea una texture 
	//SDL_FreeSurface(tmpSurface);  //Free surface.

	//playerTexture = TextureManager::LoadTexture("Assets/SuperMario.png", renderer);
	//player = new GameObject("Assets/SuperMario.png",  0, 0);
	//enemy = new GameObject("Assets/Wario.png",  50, 50);

	//newPlayer.addComponent<PositionComponent>();
	//newPlayer.getComponent<PositionComponent>().SetPos(50,50);
#pragma endregion

	xvel = GetRandomNumber(3, -3);
	yvel = GetRandomNumber(3, -3);

	if (TTF_Init() == -1)
	{
		cout << "Error : SDL_TTF\n";
	}

	assets->AddTexture("terrain", "Assets/terrain_ss.png");
	assets->AddTexture("Player", "Assets/Paddle.png");
	assets->AddTexture("Enemy", "Assets/Paddle.png");
	assets->AddTexture("BoxCollider2D", "Assets/Paddle.png");
	assets->AddTexture("Ball", "Assets/Paddle.png");

	assets->AddFont("font", "Assets/font.ttf", 44);
	assets->AddFont("fontEnemy", "Assets/font.ttf", 44);
	//assets->AddTexture("projectile", "Assets/proj.png");

	mMap = new Map("terrain", 3, 32);
	mMap->LoadMap("Assets/map.map", 25, 20);

	//ECS->Implementation:
	//tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
	//tile0.addComponent<ColliderComponent>("water");
	//tile1.addComponent<TileComponent>(100, 200, 32, 32, 1);
	//tile1.addComponent<ColliderComponent>("dirt");
	//tile2.addComponent<TileComponent>(50, 200, 32, 32, 2);
	//tile2.addComponent<ColliderComponent>("grass");

	//map = new Map("Assets/terrain_ss.png",3,22);


	//Player Paddle.
	player.addComponent<TransformComponent>(0, 800 * 0.2, 64, 12, 2);
	player.addComponent<SpriteComponent>("Player", false);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("Player", player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y, 45, 90);
	player.addGroup(groupPlayers);

	SDL_Color white = { 255,255,255,255 };

	//Label TextTitle.
	playerLabel.addComponent<UILabel>(Game::camera.w * 0.5 - 20, 0, "PONG", "font", white);
	playerLabel.addComponent<UILabel>(10, 10, to_string(playerScore), "font", white);
	enemyLabel.addComponent<UILabel>(750, 10, to_string(enemyScore), "fontEnemy", white);

	//label.addComponent<UILabel>(775, 0, to_string(enemyScore), "font", white);

	//Enemy Paddle.
	enemy.addComponent<TransformComponent>(775, 800 * 0.2 - 50, 64, 12, 2);
	enemy.addComponent<SpriteComponent>("Enemy", false);
	enemy.addComponent<ColliderComponent>("Enemy", enemy.getComponent<TransformComponent>().position.x, enemy.getComponent<TransformComponent>().position.y, 45, 90);
	enemy.addGroup(groupEnemies);

	//Up Wall.
	boxCollider2D_Up.addComponent<TransformComponent>(0, -60, 32, 800, 2);
	boxCollider2D_Up.addComponent<SpriteComponent>("BoxCollider2D", false);
	boxCollider2D_Up.addComponent<ColliderComponent>("BoxCollider2D", boxCollider2D_Up.getComponent<TransformComponent>().position.x, boxCollider2D_Up.getComponent<TransformComponent>().position.y, 25, 25);
	boxCollider2D_Up.addGroup(groupBoxCollider2D);

	//Down Wall.
	boxCollider2D_Down.addComponent<TransformComponent>(0, 590, 32, 800, 2);
	boxCollider2D_Down.addComponent<SpriteComponent>("BoxCollider2D", false);
	boxCollider2D_Down.addComponent<ColliderComponent>("BoxCollider2D", boxCollider2D_Down.getComponent<TransformComponent>().position.x, boxCollider2D_Down.getComponent<TransformComponent>().position.y, 25, 25);
	boxCollider2D_Down.addGroup(groupBoxCollider2D);

	assets->CreateBall(Vector2D(800 * 0.2, 600 * 0.2), Vector2D(xvel, yvel), 2, "Ball");

	//assets->CreateProjectile(Vector2D(500, 600), Vector2D(2, 0), 200, 2, "projectile");
	//assets->CreateBall(); //con Logica gia' inserita.
	//assets->CreateProjectile(Vector2D(500, 620), Vector2D(2, 0), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(400, 600), Vector2D(2, 1), 200, 2, "projectile");
	//assets->CreateProjectile(Vector2D(500, 600), Vector2D(2, -1), 200, 2, "projectile");

	/*wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("Assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);*/

	//water.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	//water.addComponent<SpriteComponent>("Assets/water.png");
	//water.addComponent<ColliderComponent>("water");
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& box_colliders2d(manager.getGroup(Game::groupBoxCollider2D));
auto& ball(manager.getGroup(Game::groupProjectile));

void Game::HandleEvents()
{
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
		}
	}
}

void Game::Update()
{
	SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;

	SDL_Rect enemyCol = enemy.getComponent<ColliderComponent>().collider;
	Vector2D enemyPos = enemy.getComponent<TransformComponent>().position;
	enemy.getComponent<TransformComponent>().velocity.y = player.getComponent<TransformComponent>().velocity.y;

	manager.Refresh();
	manager.Update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;

		if (Collision::AABB(cCol, playerCol))
		{
			cout << "HIT!\n";
			player.getComponent<TransformComponent>().position = playerPos;
		}

		if (Collision::AABB(cCol, enemyCol))
		{
			cout << "HIT!\n";
			enemy.getComponent<TransformComponent>().position = enemyPos;
		}
	}

	if (Collision::AABB(playerCol, enemyCol))
	{
		player.getComponent<TransformComponent>().position = playerPos;
	}

	//float prova = BallComponent::calc_angle(1, 1, 1);

	//Collision with projectiles.
	for (auto& b : ball)
	{
		if (b->getComponent<TransformComponent>().position.y < 1)
		{
			yvel = -yvel;
			//b->getComponent<TransformComponent>().position.y = -b->getComponent<TransformComponent>().position.y;
		}

		if (b->getComponent<TransformComponent>().position.y + b->getComponent<TransformComponent>().height > 599)
		{
			yvel = -yvel;
			//b->getComponent<TransformComponent>().position.y = -b->getComponent<TransformComponent>().position.y;
		}

		if (b->getComponent<TransformComponent>().position.x < 2)
		{
			/*	xvel = GetRandomNumber(2, -2);
				yvel = GetRandomNumber(2, -2);*/

			cout << "Reset\n";
			enemyScore++;
			b->getComponent<TransformComponent>().position.x = BALL_X;
			b->getComponent<TransformComponent>().position.y = BALL_Y;

			//b->getComponent<TransformComponent>().position.x = GetRandomNumber(2, -2);
			//b->getComponent<TransformComponent>().position.y = GetRandomNumber(2, -2);

			b->getComponent<TransformComponent>().position.x += xvel;
			b->getComponent<TransformComponent>().position.y += yvel;
			//b->getComponent<TransformComponent>().position.y = -b->getComponent<TransformComponent>().position.y;
		}

		if (b->getComponent<TransformComponent>().position.x + b->getComponent<TransformComponent>().width > 798)
		{
			/*	xvel = GetRandomNumber(2, -2);
				yvel = GetRandomNumber(2, -2);*/
			playerScore++;
			b->getComponent<TransformComponent>().position.x = BALL_X;
			b->getComponent<TransformComponent>().position.y = BALL_Y;

			//b->getComponent<TransformComponent>().position.x = GetRandomNumber(2, -2);
			//b->getComponent<TransformComponent>().position.y = GetRandomNumber(2, -2);
			//b->getComponent<TransformComponent>().position.y = -b->getComponent<TransformComponent>().position.y;
		}

		if (Collision::AABB(playerCol, b->getComponent<ColliderComponent>().collider))
		{
			xvel = -xvel;
			//b->getComponent<TransformComponent>().velocity.x = -b->getComponent<TransformComponent>().velocity.x;
			//b->Destroy();
		}

		if (Collision::AABB(enemyCol, b->getComponent<ColliderComponent>().collider))
		{
			xvel = -xvel;
			//b->getComponent<TransformComponent>().velocity.x = -b->getComponent<TransformComponent>().velocity.x;
		}

		b->getComponent<TransformComponent>().position.x += xvel;
		b->getComponent<TransformComponent>().position.y += yvel;
	}

	for (auto& boxs : box_colliders2d)
	{
		SDL_Rect cCol = boxs->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			cout << "HIT!\n";
			player.getComponent<TransformComponent>().position = playerPos;
		}

		if (Collision::AABB(cCol, enemyCol))
		{
			cout << "HIT!\n";
			enemy.getComponent<TransformComponent>().position = enemyPos;
		}
	}

	playerLabel.getComponent<UILabel>().SetLabelText(to_string(playerScore),"font");
	enemyLabel.getComponent<UILabel>().SetLabelText(to_string(enemyScore), "fontEnemy");

	//camera.x = player.getComponent<TransformComponent>().position.x;
	//camera.y = player.getComponent<TransformComponent>().position.y;

	//if (camera.x < 0)
	//	camera.x = 0;
	//if (camera.y < 0)
	//	camera.y = 0;
	//if (camera.x > camera.w)
	//	camera.x = camera.w;
	//if (camera.y > camera.h)
	//	camera.y = camera.h;


	//Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	//int pSpeed = player.getComponent<TransformComponent>().speed;

	//for (auto t : tiles)
	//{
	//	t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
	//	t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	//	//cout << typeid(t->getComponent<TileComponent>().destRect.x).name();
	//}

	//CollisionDetection.
	//if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
	//for (auto cc : colliders)
	//{
		//Collision::AABB(player.getComponent<ColliderComponent>(), *cc);

	//{
			//player.getComponent<TransformComponent>().velocity * -1;
		//}


	//player.getComponent<TransformComponent>().scale = 1;
		//player.getComponent<TransformComponent>().velocity * -1;
		//cout << "Wall Hit!\n";
	//}
	//else
	//{
	//	player.getComponent<TransformComponent>().scale = 2;
	//}


#pragma region Comment
	//destRect.w = 32;
	//destRect.h = 32;

	//player->Update();
	//enemy->Update();
	/*player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
	enemy.getComponent<TransformComponent>().position.Add(Vector2D(5, 5));

	if (player.getComponent<TransformComponent>().position.x > 100)
	{
		player.getComponent<SpriteComponent>().SetTex("Assets/Wario.png");
	}*/
	//cnt++;
	//cout << "Counter:\t" << cnt << endl;
	//cout << newPlayer.getComponent<PositionComponent>().x() << "\t" << newPlayer.getComponent<PositionComponent>().y() << endl;
#pragma endregion
}

void Game::Renderer()
{
	SDL_RenderClear(renderer);

	for (auto& t : tiles)
	{
		t->Draw();
	}

	//for (auto& c : colliders)
	//{
	//	c->Draw();
	//}

	for (auto& p : players)
	{
		//p->getComponent<ColliderComponent>().Draw();
		p->Draw();
	}

	for (auto& box : box_colliders2d)
	{
		//box->getComponent<ColliderComponent>().Draw();
		box->Draw();
	}

	for (auto& b : ball)
	{
		b->Draw();
	}

	for (auto& e : enemies)
	{
		e->Draw();
	}

	playerLabel.Draw();
	enemyLabel.Draw();
	//map->DrawMap();
	//manager.draw();
	SDL_RenderPresent(renderer);

#pragma region Comment
	//player->Render();		//RenderCopy();
	//enemy->Render();
	//SDL_RenderCopy(renderer, playerTexture, NULL, &destRect);  //Draw Image/Texture.
#pragma endregion

}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned!\n";
}

//void Game::AddTile(int srcX, int srcY, int x, int y)
//{
//	//auto& tile(manager.addEntity());
//	//tile.addComponent<TileComponent>(srcX, srcY, x, y, mapFile);
//	////tile.addComponent<TileComponent>(x, y, 32, 32, id);
//	//tile.addGroup(groupMap);
//
//}
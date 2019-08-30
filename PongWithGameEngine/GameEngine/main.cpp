// GameEngine.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
#include "pch.h"
#include "Game.h"

Game *game = nullptr;

//limit frame rate.
const int FPS = 60;
const int frameDelay = 1000 / FPS;

Uint32 frameStart;
int frameTime;

int main(int argc, char *argv[])
{
	game = new Game();

	game->Init("2D_GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	/*  While cycle.
	while(game is running)
	{
		handle any user input.
		update all object.
		render changes to the display.
	}
	*/

	while (game->Running())
	{
		frameStart = SDL_GetTicks();
		
		game->HandleEvents();
		game->Update();
		game->Renderer();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->Clean();

#pragma region	InitializeWindow
	/*SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_Delay(3000);*/
#pragma endregion

	return 0;
}


#include "game.h"
#include "load_image.h"
#include "player.h"
#include "map.h"


player* pacman;
SDL_Renderer* Game::renderer = nullptr;
map* gamemap;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
		pacman = new player("image/1.png", 560, 480, 3);
		gamemap = new map;
		gamemap->create_map();
	}
}

int d = 0;

void Game::handleEvents()
{
	SDL_Event e;
	if(SDL_PollEvent(&e) == 0){}
    else if(e.type == SDL_QUIT){
            isRunning = false;
    }
    else if(e.type == SDL_KEYDOWN){
        std::cout << SDL_GetKeyName(e.key.keysym.sym) << std::endl;
        switch(e.key.keysym.sym){
            case SDLK_w:
            d = 0;
            //pacman->action(d);
            break;

            case SDLK_d:
            d = 1;
            //pacman->action(d);
            break;

            case SDLK_s:
            d = 2;
            //pacman->action(d);
            break;

            case SDLK_a:
            d = 3;
            //pacman->action(d);
            break;

            default:
            break;
            }
    }

}

void Game::update()
{

    pacman->action(d);
    gamemap->update_map(pacman->xpos, pacman->ypos);

}

void Game::render()
{
	SDL_RenderClear(renderer);
	gamemap->loadmap();
	pacman->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

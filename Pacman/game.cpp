#include "game.h"
#include "load_image.h"
#include "player.h"
#include "map.h"
#include "ghost.h"
#include <cstdlib>
#include <ctime>


player* pacman;
ghost* red;
ghost* pink;
ghost* blue;
ghost* orange;

SDL_Renderer* Game::renderer = nullptr;
map* gamemap;
const int fps = 60;
int safe_house_x, safe_house_y;

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
		pacman = new player("image/pacman.png", 560, 480, 3);
		red = new ghost(40, 40, 0);
		pink = new ghost(1120, 40, 1);
		blue = new ghost(120, 640, 2);
		orange = new ghost(1040, 640, 3);
		gamemap = new map;
		gamemap->create_map();
		cherri = gamemap->cherri_left;
		gamemap->get_safehouse(safe_house_x, safe_house_y);
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
        switch(e.key.keysym.sym){
            case SDLK_d:
            d = 0;
            break;

            case SDLK_s:
            d = 1;
            break;

            case SDLK_a:
            d = 2;
            break;

            case SDLK_w:
            d = 3;
            break;

            default:
            break;
            }
    }

}
int change_frame = 0, speed = 6;

void Game::update()
{
    if(gamemap->win()){
        isRunning = false;
        std::cout << "You Won !!!" << std::endl;
    }

    if(pacman->dead){
        isRunning = false;
        std::cout << "Game Over !" << std::endl;
    }
    change_frame++;
    if(fps / change_frame == speed){
        change_frame = 0;
        pacman->sprite(d);
    }
    int x = pacman->xpos, y = pacman->ypos;
    int x_rand = rand() % 1200 + 1, y_rand = rand() % 800 + 1;

    pacman->action(d);

    if(red->eaten){
        red->chase(safe_house_x, safe_house_y, red->facing, red->scare);
        if(red->got_to_safehouse(safe_house_x, safe_house_y)) red->eaten = false;
    }else{
        red->chase(x, y, red->facing, red->scare);
    }

    if(pink->eaten){
        pink->chase(safe_house_x, safe_house_y, pink->facing, pink->scare);
        if(pink->got_to_safehouse(safe_house_x, safe_house_y)) pink->eaten = false;
    }else{
        pink->chase(x_rand, y_rand, pink->facing, pink->scare);
    }

    if(blue->eaten){
        blue->chase(safe_house_x , safe_house_y, blue->facing, blue->scare);
        if(blue->got_to_safehouse(safe_house_x, safe_house_y)) blue->eaten = false;
    }else{
        blue->chase(x_rand , x_rand, blue->facing, blue->scare);
    }

    if(orange->eaten){
        orange->chase(safe_house_x, safe_house_y, orange->facing, orange->scare);
        if(orange->got_to_safehouse(safe_house_x, safe_house_y)) orange->eaten = false;
    }else{
        orange->chase(y_rand , y_rand, orange->facing, orange->scare);
    }

    gamemap->update_map(x, y);

    if(red->meet(x, y, red->scare, red->eaten) || pink->meet(x, y, pink->scare, pink->eaten) || blue->meet(x, y, blue->scare, blue->eaten) || orange->meet(x, y, orange->scare, orange->eaten)){
        pacman->dead = true;
    }

}

int timer = 0;

void Game::render()
{
	SDL_RenderClear(renderer);
	gamemap->loadmap();
	pacman->render();
	if(cherri != gamemap->cherri_left){
        timer++;
        red->scare = true;
        pink->scare = true;
        blue->scare = true;
        orange->scare = true;
        if(timer == 500){
            cherri = gamemap->cherri_left;
            timer = 0;
            red->scare = false;
            pink->scare = false;
            blue->scare = false;
            orange->scare = false;
        }
	}
	red->render(cherri, red->scare, red->eaten);
	pink->render(cherri, pink->scare, pink->eaten);
	blue->render(cherri, blue->scare, blue->eaten);
	orange->render(cherri, orange->scare, orange->eaten);
	SDL_RenderPresent(renderer);
    std::cout << timer << std::endl;
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

#include "game.h"
#include "load_image.h"
#include "player.h"
#include "map.h"
#include "ghost.h"
#include "pen.h"
#include <cstdlib>
#include <ctime>


player* pacman;
ghost* red;
ghost* pink;
ghost* blue;
ghost* orange;

SDL_Renderer* Game::renderer = nullptr;
map* gamemap;
pen* p;

const int fps = 60;
int safe_house_x, safe_house_y;


Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen){
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO ) == 0){
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		TTF_Init();
		if (renderer){
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}

    pacman = new player("image/pacman.png", 560, 480, 3);
    red = new ghost(40, 40, 0);
    pink = new ghost(1120, 40, 1);
    blue = new ghost(120, 640, 2);
    orange = new ghost(1040, 640, 3);
    p = new pen(30);
    gamemap = new map;
    gamemap->create_map();
    cherri = gamemap->cherri_left;
    gamemap->get_safehouse(safe_house_x, safe_house_y);

    waka = Mix_LoadMUS("sound/waka.mp3");
	power = Mix_LoadMUS("sound/scare.mp3");
	die = Mix_LoadWAV("sound/dead.wav");
    player_lives = Texture::NewTexture("image/1up.png");
    win_screen = Texture::NewTexture("image/youwon.png");
    pause_screen = Texture::NewTexture("image/pause.png");
    retry_screen = Texture::NewTexture("image/retry.png");
    lost_screen = Texture::NewTexture("image/gameover.png");


    isRunning = true;
    is_pause = true;
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
            case SDLK_r:
            if(pacman->dead){
                lives--;
                is_pause = true;
                if(lives >= 0){
                    pacman->retry();
                    red->retry(red->spaw_x, red->spaw_y);
                    pink->retry(pink->spaw_x, pink->spaw_y);
                    blue->retry(blue->spaw_x, blue->spaw_y);
                    orange->retry(orange->spaw_x, orange->spaw_y);
                }

            }
            break;

            case SDLK_d:
            is_pause = false;
            d = 0;
            break;

            case SDLK_s:
            is_pause = false;
            d = 1;
            break;

            case SDLK_a:
            is_pause = false;
            d = 2;
            break;

            case SDLK_w:
            is_pause = false;
            d = 3;
            break;

            case SDLK_m:
            is_pause = false;
            if(is_muted){
                is_muted = false;
            }else{
                is_muted = true;
            }
            break;

            case SDLK_ESCAPE:
            isRunning = false;
            break;

            case SDLK_p:
            if(!is_pause){
                is_pause = true;
            }else{
                is_pause = false;
            }
            break;

            default:
            if(is_pause){
                is_pause = false;
            }
            break;
            }
    }

}
int change_frame = 0, speed = 5;

void Game::update()
{
    if(gamemap->win()){
        is_pause = true;
    }

    if(lives == 0){
        isRunning = false;
    }
    change_frame++;
    if((fps / change_frame) == speed and !pacman->dead){
        change_frame = 0;
        pacman->sprite(d);
    }
    else if((fps / change_frame) == speed and pacman->dead){
        change_frame = 0;
        pacman->dying_animation();
    }
    int x = pacman->xpos, y = pacman->ypos;
    int x_rand = rand() % 1200 + 1, y_rand = rand() % 800 + 1;



    if(!pacman->dead){
        pacman->action(d);
        if(red->eaten){
            red->chase(safe_house_x, safe_house_y, red->facing, red->eaten);
            if(red->got_to_safehouse(safe_house_x, safe_house_y)){
                red->eaten = false;
                red->scare = false;
                red->revive(safe_house_x, safe_house_y);
            }
        }else{
            red->chase(x, y, red->facing, red->eaten);
        }

        if(pink->eaten){
            pink->chase(safe_house_x, safe_house_y, pink->facing, pink->eaten);
            if(pink->got_to_safehouse(safe_house_x, safe_house_y)){
                pink->eaten = false;
                pink->scare = false;
                pink->revive(safe_house_x, safe_house_y);
            }
        }else{
            pink->chase(red->xcoor, red->ycoor, pink->facing, pink->eaten);
        }

        if(blue->eaten){
            blue->chase(safe_house_x , safe_house_y, blue->facing, blue->eaten);
            if(blue->got_to_safehouse(safe_house_x, safe_house_y)){
                blue->eaten = false;
                blue->scare = false;
                blue->revive(safe_house_x, safe_house_y);
            }
        }else{
            blue->chase(x_rand , x_rand, blue->facing, blue->eaten);
        }

        if(orange->eaten){
            orange->chase(safe_house_x, safe_house_y, orange->facing, orange->eaten);
            if(orange->got_to_safehouse(safe_house_x, safe_house_y)){
                orange->eaten = false;
                orange->scare = false;
                orange->revive(safe_house_x, safe_house_y);
            }
        }else{
            orange->chase(x_rand , y_rand, orange->facing, orange->eaten);
        }
    }

    gamemap->update_map(x, y, score);
    if(red->meet(x, y, red->scare, red->eaten, score) || pink->meet(x, y, pink->scare, pink->eaten, score) || blue->meet(x, y, blue->scare, blue->eaten, score) || orange->meet(x, y, orange->scare, orange->eaten, score)){
        pacman->dead = true;
    }

}

int scare_timer = 0;

void Game::render()
{
	SDL_RenderClear(renderer);
	gamemap->loadmap();
    p->write("score: " + std::to_string(score) , 1200, 600, {255, 255, 255, 255});
    p->write("Best: " + std::to_string(high_score) , 1200, 650, {255, 255, 255, 255});
    p->write("CONTROL:" , 1205, 0, {255, 255, 255, 255});
    p->write("ASWD to move" , 1205, 50, {255, 255, 255, 255});
    p->write("M to mute" , 1205, 100, {255, 255, 255, 255});
    p->write("P to pause" , 1205, 150, {255, 255, 255, 255});
    p->write("Esc to quit" , 1205, 200, {255, 255, 255, 255});


	if(cherri != gamemap->cherri_left){
        scare_timer++;
        red->scare = true;
        pink->scare = true;
        blue->scare = true;
        orange->scare = true;
        if(scare_timer == 500){
            cherri = gamemap->cherri_left;
            scare_timer = 0;
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
	pacman->render();
}

void Game::render_all(){
    render_rect.x = 1210; render_rect.y = 700;
    render_rect.h = 40; render_rect.w = 40;
    for(int i = 0; i < lives; i++){
        SDL_RenderCopy(renderer, player_lives, NULL, &render_rect);
        render_rect.x += render_rect.w + 10;
    }
    if(gamemap->win()){
        render_rect.x = 230; render_rect.y = 300;
        render_rect.h = 100; render_rect.w = 750;
        SDL_RenderCopy(renderer, win_screen, NULL, &render_rect);
        if(score == high_score){
            p->write("__New High Score__", 500, 550,{255, 255, 255, 255});
        }
    }

    if(is_pause and lives != 0 and !pacman->dead){
        render_rect.x = 230; render_rect.y = 300;
        render_rect.h = 100; render_rect.w = 750;
        SDL_RenderCopy(renderer, pause_screen, NULL, &render_rect);
    }
    if(pacman->dead){
        render_rect.x = 230; render_rect.y = 300;
        render_rect.h = 100; render_rect.w = 750;
        SDL_RenderCopy(renderer, retry_screen, NULL, &render_rect);
    }
    if(lives == 0){
        render_rect.x = 200; render_rect.y = 300;
        render_rect.h = 100; render_rect.w = 750;
        SDL_RenderCopy(renderer, lost_screen, NULL, &render_rect);
        if(score == high_score){
            p->write("__New High Score__", 500, 550,{255, 255, 255, 255});
        }
    }
    SDL_RenderPresent(renderer);
}

bool flag, flag2 = false;

void Game::play_sound(){
    if(!is_muted){
        if(flag != red->scare){
            Mix_HaltMusic();
            flag = red->scare;
        }
        if(flag2 != pacman->dead && pacman->dead){
            Mix_HaltMusic();
            Mix_PlayChannel(-1, die, 0);
        }
        flag2 = pacman->dead;
        if(is_pause || pacman->dead){
            Mix_HaltMusic();
            return;
        }

        if(red->scare && !Mix_PlayingMusic()){
            Mix_HaltMusic();
            Mix_PlayMusic(power, 0);
        }
        if(!red->scare && !Mix_PlayingMusic()){
            Mix_HaltMusic();
            Mix_PlayMusic(waka, 0);
        }

    }
    else{
        Mix_HaltMusic();
        return;
    }

}

void Game::clean()
{

    Mix_CloseAudio();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

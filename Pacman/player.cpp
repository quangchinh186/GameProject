#include "player.h"
#include "load_image.h"
#include "map.h"

map* player_map;
int f = 0;

player::player(const char* filename, int x, int y, int f){
    frame = f;
    playerTex = Texture::NewTexture(filename);
    dyingPlayer = Texture::NewTexture("image/dead.png");
    sR.x = 0;
    sR.y = 0;
    sR.h = 50;
    sR.w = 50;

    dR.h = 40;
    dR.w = 40;
    dR.x = x; xpos = x;
    dR.y = y; ypos = y;

    spawn_x = x;
    spawn_y = y;

    player_map = new map;
    player_map->create_map();
}
player::~player(){}


void player::sprite(int direct){
    if(sR.y < sR.h*frame*direct || sR.y >= sR.h*frame*(direct + 1) - sR.h){
        sR.y = sR.h * frame * direct;
    }else{
        sR.y += sR.h;
    }

    if(dead){
        sR.y = 0;
    }
}

void player::retry(){
    f = 0;
    dead = false;
    sR.y = 0;
    dR.x = spawn_x;
    dR.y = spawn_y;
}

int x_step[4] = {1, 0, -1, 0};
int y_step[4] = {0, 1, 0, -1};
int v = 5, sub = 0;

void player::action(int direct){
    xpos = dR.x;
    ypos = dR.y;
    if(player_map->turnable(xpos, ypos)){
        dR.x += v * x_step[direct];
        dR.y += v * y_step[direct];
        if(player_map->moveable(xpos+(dR.w*x_step[direct]), ypos+(dR.h*y_step[direct]), false)){}
        else{
        dR.x = xpos;
        dR.y = ypos;
        }
    }
    else{
        dR.x += v * x_step[sub];
        dR.y += v * y_step[sub];
        direct = sub;
    }

    sub = direct;
}


void player::dying_animation(){
    sR.y = f*sR.h;
    f++;
}

void player::render(){
    if(dead){
        SDL_RenderCopy(Game::renderer, dyingPlayer, &sR, &dR);
    }
    else{
        SDL_RenderCopy(Game::renderer, playerTex, &sR, &dR);
    }

}

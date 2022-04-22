#include "player.h"
#include "load_image.h"
#include "map.h"

map* player_map;

player::player(const char* filename, int x, int y, int f){
    frame = f;
    playerTex = Texture::NewTexture(filename);
    sR.x = 0;
    sR.y = 0;
    sR.h = 50;
    sR.w = 50;

    dR.h = 40;
    dR.w = 40;
    dR.x = x; xpos = x;
    dR.y = y; ypos = y;

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
}

int x_step[4] = {1, 0, -1, 0};
int y_step[4] = {0, 1, 0, -1};
int v = 5;

void player::action(int direct){
    xpos = dR.x;
    ypos = dR.y;
    dR.x += v * x_step[direct];
    dR.y += v * y_step[direct];
    int x = dR.x, y = dR.y, t;
    //di tien theo chieu duong cua Ox can cong them phan thieu de kiem tra tiep xuc voi wall
    /*
    if(dR.x > xpos){
        x += (dR.w - v);
    }
    if(dR.y > ypos){
        y += (dR.h - v);
    }*/
    //khi di chuyen thi se di dung theo rect cua map


    if(player_map->moveable(x, y, v)){
        if(dR.x == xpos){
        t = dR.x % dR.w;
        t >= (dR.w - t) ? dR.x += (dR.w - t) : dR.x -= t;
    }
    if(dR.y == ypos){
        t = dR.y % dR.h;
        t >= (dR.h - t) ? dR.y += (dR.h - t) : dR.y -= t;
    }
    }
    else{
        dR.x = xpos;
        dR.y = ypos;
    }
}

void player::render(){
    SDL_RenderCopy(Game::renderer, playerTex, &sR, &dR);
}

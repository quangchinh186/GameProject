#include "player.h"
#include "load_image.h"
#include "map.h"

map* gm;

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

    gm = new map;
    gm->create_map();
}
player::~player(){}


void player::sprite(int direct){
    if(sR.y < 150*direct || sR.y >= 150*(direct + 1)-50){
        sR.y = 150 * direct;
    }else{
        sR.y += 50;
    }


}

int x_step[4] = {1, 0, -1, 0};
int y_step[4] = {0, 1, 0, -1};

void player::action(int direct){
    xpos = dR.x;
    ypos = dR.y;
    dR.x += 5 * x_step[direct];
    dR.y += 5 * y_step[direct];
    int x = dR.x, y = dR.y, t;
    if(dR.x > xpos){
        x += 35;
    }
    if(dR.x == xpos){
        t = dR.x % 40;
        t >= (40-t) ? dR.x += (40-t) : dR.x -= t;
    }
    if(dR.y > ypos){
        y += 35;
    }
    if(dR.y == ypos){
        t = dR.y % 40;
        t >= (40-t) ? dR.y += (40-t) : dR.y -= t;
    }

    if(gm->moveable(x, y)){}
    else{
        dR.x = xpos;
        dR.y = ypos;
    }

    std::cout << dR.x << " " << dR.y << std::endl;
}

void player::render(){
    SDL_RenderCopy(Game::renderer, playerTex, &sR, &dR);
}

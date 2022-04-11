#include "player.h"
#include "load_image.h"
#include "map.h"

player::player(const char* filename, int x, int y, int f){
    frame = f;
    playerTex = Texture::NewTexture(filename);
    sR.x = 0;
    sR.y = 0;
    sR.h = 200;
    sR.w = 200;

    dR.h = 40;
    dR.w = 40;
    dR.x = x;
    dR.y = y;
}
player::~player(){}

void player::ilde(){
    sR.x = 600 / (SDL_GetTicks() % frame + 1);
}
/*
bool player::check_colide(dR.x, dR.y){


    return true;
}*/

int x_step[4] = {0, 1, 0, -1};
int y_step[4] = {-1, 0, 1, 0};

void player::action(int direct){
    //if(check_colide == false){}
    //else{
        dR.x += 5 * x_step[direct];
        dR.y += 5 * y_step[direct];
        SDL_Delay(10);
    //}

    std::cout << dR.x << " " << dR.y << std::endl;
}

void player::render(){
    SDL_RenderCopy(Game::renderer, playerTex, &sR, &dR);
}

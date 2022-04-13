#include "player.h"
#include "load_image.h"
#include "map.h"

map* gm;

player::player(const char* filename, int x, int y, int f){
    frame = f;
    playerTex = Texture::NewTexture(filename);
    sR.x = 0;
    sR.y = 0;
    sR.h = 200;
    sR.w = 200;

    dR.h = 40;
    dR.w = 40;
    dR.x = x; xpos = x;
    dR.y = y; ypos = y;

    gm = new map;
    gm->create_map();
}
player::~player(){}

void player::ilde(){
    sR.x = 600 / (SDL_GetTicks() % frame + 1);
}
/*
void player::check_position(){
    int row = dR.y / 40;
    int col = dR.x / 40;

    if(m[row][col] == 1){
        colide = true;
    }else{
        colide = false;
    }
}*/

int x_step[4] = {0, 1, 0, -1};
int y_step[4] = {-1, 0, 1, 0};

void player::action(int direct){
        xpos = dR.x;
        ypos = dR.y;
        dR.x += 5 * x_step[direct];
        dR.y += 5 * y_step[direct];
        if(gm->moveable(dR.x, dR.y)){}
        else{
            dR.x = (xpos/40) *40;
            dR.y = (ypos/40) *40;
        }



        //SDL_Delay(50);

    std::cout << xpos << " " << ypos << std::endl;
}

void player::render(){
    SDL_RenderCopy(Game::renderer, playerTex, &sR, &dR);
}

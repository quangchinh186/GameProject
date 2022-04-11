#include "map.h"

map::map(){
    wall = Texture::NewTexture("image/wall.png");
    blank = Texture::NewTexture("image/blank.png");
    item = Texture::NewTexture("image/item.jpg");
    destR.x = destR.y = 0;
    destR.w = 40;
    destR.h = 40;
}
map::~map(){}


void map::drawmap(SDL_Texture *tex){
    SDL_RenderCopy(Game::renderer, tex, NULL, &destR);
}

void map::loadmap(){

    for(int i = 0; i < 20 ; i++){
        for(int j = 0; j < 30; j++){
            destR.x = 40*j;
            destR.y = 40*i;
            if(m[i][j] == 0){
                SDL_RenderCopy(Game::renderer, blank, NULL, &destR);
            }else if(m[i][j] == 1){
                SDL_RenderCopy(Game::renderer, wall, NULL, &destR);
            }
            else{
                SDL_RenderCopy(Game::renderer, item, NULL, &destR);
            }

        }
    }
}



#include "map.h"


map::map(){
    wall = Texture::NewTexture("image/wall.png");
    blank = Texture::NewTexture("image/blank.png");
    item = Texture::NewTexture("image/item.jpg");
    cherri = Texture::NewTexture("image/cherri.jpg");
    gate = Texture::NewTexture("image/gate.jpg");
    destR.x = destR.y = 0;
    destR.w = 40;
    destR.h = 40;
}
map::~map(){}

void map::create_map(){
    std::ifstream file;
    file.open("map.txt");
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 30; j++){
            file >> m[i][j];
        }
    }
    file.close();
}

bool map::moveable(int x, int y){
    int j = x / destR.w, i = y / destR.h;
    if(m[i][j] == 1 ){
        return false;
    }
    return true;
}

bool map::turnable(int x, int y){
    if(x % destR.w == 0 and y % destR.h == 0){
        return true;
    }

    return false;
}

void map::update_map(int x, int y){
    if(x % 40 <= 20 and y % 40 <= 20){
        int j = x/40, i = y/40;
        if(m[i][j] == 2){
            m[i][j] = 0;
        }
        if(m[i][j] == 3){
            m[i][j] = 0;
            cherri_left--;
        }
    }
}

bool map::win(){
    bool cnt = true;
    for(int i = 0; i < 20 ; i++){
        for(int j = 0; j < 30; j++){
            if(m[i][j] == 2){
                cnt = false;
            }
        }
    }

    return cnt;
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
            }else if(m[i][j] == 3){
                SDL_RenderCopy(Game::renderer, cherri, NULL, &destR);
            }else if(m[i][j] == 4){
                SDL_RenderCopy(Game::renderer, gate, NULL, &destR);
            }else{
                SDL_RenderCopy(Game::renderer, item, NULL, &destR);
            }

        }
    }
}

void map::get_safehouse(int& x, int& y){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 30; j ++){
            if(m[i][j] == 4){
                x = destR.w * (j+1);
                y = destR.h * (i+1);
            }
        }
    }
}

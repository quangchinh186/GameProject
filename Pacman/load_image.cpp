#include "load_image.h"


SDL_Texture* Texture::NewTexture(const char* file){
    SDL_Texture* tex;
    SDL_Surface* temp = IMG_Load(file);
    tex = SDL_CreateTextureFromSurface(Game::renderer, temp);
    SDL_FreeSurface(temp);

    return tex;
}

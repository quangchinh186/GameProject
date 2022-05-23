#include "pen.h"

pen::pen(){

}

pen::~pen(){
    TTF_CloseFont(font);
}

void pen::write(const std::string &msg, int x, int y, SDL_Color color, int size)
{
    font = TTF_OpenFont("font.ttf", size);
    SDL_Surface *surf;
    SDL_Texture *tex;
    SDL_Rect rect;
    surf = TTF_RenderText_Solid(font, msg.c_str(), color);
    tex = SDL_CreateTextureFromSurface(Game::renderer, surf);
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;
    SDL_FreeSurface(surf);
    SDL_RenderCopy(Game::renderer, tex, NULL, &rect);
    SDL_DestroyTexture(tex);

}

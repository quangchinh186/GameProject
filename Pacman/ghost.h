#ifndef ghost_h
#define ghost_h

#include "game.h"
#include "load_image.h"

class ghost{
public:
    ghost(int x, int y, int color);
    ~ghost();
    void render(int cherri);
    void chase(int x, int y, int direct, bool& d);
    void sprite(int direct);

private:
    SDL_Texture* ghost_tex;
    SDL_Texture* ghost_scare;
    SDL_Texture* ghost_eaten;
    SDL_Rect desR, srcR;
    bool eaten;
    bool scare;
};


#endif // ghost_h

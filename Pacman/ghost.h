#ifndef ghost_h
#define ghost_h

#include "game.h"
#include "load_image.h"

class ghost{
public:
    ghost(int x, int y, int color);
    ~ghost();
    void render();
    void chase(int x, int y, int direct);
    void sprint(int direct);
    bool meet(int x, int y);
    void change_form();

private:
    SDL_Texture* ghost_tex;
    SDL_Texture* ghost_scare;
    SDL_Texture* ghost_eaten;
    SDL_Rect desR, srcR;
    bool eaten = false;
    bool scare = false;
};


#endif // ghost_h

#ifndef ghost_h
#define ghost_h

#include "game.h"
#include "load_image.h"

class ghost{
public:
    ghost(int x, int y, int _color);
    ~ghost();
    void render(int cherri, bool& sc, bool& ate);
    void chase(int x, int y, int& face, bool ate);

    int xcoor, ycoor, source, facing = 0;
    int temp_face = 0;
    int ghost_v = 4;
    bool meet(int x, int y, bool& sc, bool& ate);
    void go_to_safehouse();
    bool eaten;
    bool scare;

private:
    SDL_Texture* ghost_tex;
    SDL_Texture* ghost_scare;
    SDL_Texture* ghost_eaten;
    SDL_Rect desR, srcR;

};


#endif // ghost_h

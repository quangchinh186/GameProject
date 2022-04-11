#ifndef image_h
#define image_h
#include "game.h"

class Texture{

public:
    static SDL_Texture* NewTexture(const char* file);

};

#endif // image_h

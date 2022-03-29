#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "My Game";

//bool Painter::createImage( SDL_Texture* texture )
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
const int v = 5;
int x_step[5] = {0, 0, 1, 0, -1};
int y_step[5] = {0, -1, 0, 1, 0};

void run(int &x, int &y, int direct){
    x+= x_step[direct] * v;
    y+= y_step[direct] * v;
}

string pacman_status[3] = {"resources/head_right_pacman_open.png", "resources/head_right_pacman_half.png", "resources/pacman_full.png"};

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer );

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    SDL_Rect object;
    object.x = 0; object.y = 0; object.h = 40; object.w = 40;


    SDL_Texture* pacman = loadTexture(pacman_status[0], renderer);
    SDL_RenderCopy(renderer, pacman, 0, &object);
    SDL_RenderPresent(renderer);
    int idle, direction = 2;
    SDL_Event e;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    while (true) {
        idle = (SDL_GetTicks()/100 )% 3;
        pacman = loadTexture(pacman_status[idle], renderer);

        if(SDL_PollEvent(&e) == 0){}
        else if(e.type == SDL_QUIT){break;}
        else if(e.type == SDL_KEYDOWN){
            cout << SDL_GetKeyName(e.key.keysym.sym) << " " << angle << endl;
            switch(e.key.keysym.sym){
                case SDLK_w:
                    if(direction == 3){
                        angle+=180;
                    }else if(direction == 2){
                        angle += 270;
                    }
                    else if(direction == 4){
                        angle += 90;
                    }
                    direction = 1;
                    break;
                    /////////
                case SDLK_a:
                    if(direction == 2){
                        angle += 180;
                    }else if(direction == 3){
                        angle += 90;
                    }
                    else if(direction == 1){
                        angle += 270;
                    }
                    direction = 4;
                    break;
                    /////////////
                case SDLK_s:
                    if(direction == 1){
                        angle+=180;
                    }else if(direction == 2){
                        angle += 90;
                    }
                    else if(direction == 4){
                        angle += 270;
                    }
                    direction = 3;
                    break;
                    ///////////
                case SDLK_d:
                    if(direction == 4){
                        angle+=180;
                    }else if(direction == 1){
                        angle += 90;
                    }
                    else if(direction == 3){
                        angle += 270;
                    }
                    direction = 2;
                    break;
            }
        }
        run(object.x, object.y, direction);

        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, pacman, NULL, &object, angle, NULL, flip);
        SDL_RenderPresent(renderer);
        if(angle > 360)angle -= 360;
    }


    quitSDL(window, renderer);
    return 0;
}

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}


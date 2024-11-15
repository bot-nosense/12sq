#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_BPP = 32;

SDL_Surface* g_screen = NULL;
SDL_Surface* g_background = NULL;
SDL_Event g_background;

void init()
{

}


SDL_Surface* loadImage(std::string filePath)
{
    SDL_Surface* load_image = NULL;
    SDL_Surface* optimal_image = NULL;

    load_image = IMG_Load(filePath.c_str());
    if (load_image == NULL)
        std::cout << "Load image fail." << std::endl;
    else
        optimal_image = SDL_ConvertSurfaceFormat(load_image, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(load_image);
    return optimal_image;
}

int main(int argc, char* args[])
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* image = NULL;
    bool isRunning = true;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 600, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_Quit();
        return 1;
    }

    screenSurface = SDL_GetWindowSurface(window);
    image = loadImage("bg2.png");
    if (image == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    while (isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                int response = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
                    "Xác nhận thoát",
                    "Bạn có chắc chắn muốn thoát khỏi trò chơi không?",
                    window);
                if (response == 0)  isRunning = false;
            }
        }

        SDL_BlitSurface(image, NULL, screenSurface, NULL);
        SDL_UpdateWindowSurface(window);
    }

    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
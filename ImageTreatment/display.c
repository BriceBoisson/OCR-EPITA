#include "display.h"

void wait_for_keypressed()
{
    SDL_Event event;

    
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}


SDL_Window* display_img(SDL_Surface* image)
{
    if(SDL_VideoInit(NULL) < 0)// Initialize SDL
    {
        printf("Error of initializing SDL : %s",SDL_GetError());
    }

    // Create window
    SDL_Window* fenetre;

    int w = image -> w;// width of the bmp
    int h = image -> h;// height of the bmp

    fenetre = SDL_CreateWindow("OCR", SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE);

    if(fenetre == NULL)// if problem return error
    {
        printf("Error of creating window : %s",SDL_GetError());
    }


    SDL_BlitSurface(image, NULL, SDL_GetWindowSurface(fenetre), 0);
    SDL_UpdateWindowSurface(fenetre);

    return fenetre;
}

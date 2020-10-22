#include "cleanerimage.h"
#include "segmentation.h"



int main()
{

    SDL_Surface *loadedImage = 0;
        loadedImage = SDL_LoadBMP("src/save.bmp");

    
    loadedImage = resize(loadedImage,3000,3000);
  

    SDL_SaveBMP(loadedImage,"src/final.bmp");

    return 0;
}
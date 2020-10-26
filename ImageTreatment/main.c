#include "Filter/cleanerimage.h"
#include "Segmentation/segmentation.h"
#include <string.h>
#include "display.h"


int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        printf("Welcome to our Image treatment.\n The following command are avaible : \n -Grayscale \n -Binerize \n -CutCharactere \n -RLSAh \n -RLSAv \n");
        return 1;
    }

    
    if (argc < 3) {
		printf("Error, two arguments needed.\n");
		return 1;
	}


    SDL_Surface *loadedImage = 0;
    loadedImage = SDL_LoadBMP(argv[2]);

    SDL_Window *window = display_img(loadedImage);

    wait_for_keypressed();

    

    if (!loadedImage)
    {
        printf("Can't find the bmp file\n");
        return 1;
    }

    if (strcmp(argv[1], "grayscale") == 0) {
        grayscale(loadedImage);
        window = display_img(loadedImage);
        wait_for_keypressed();
    }

    if (strcmp(argv[1], "CutCharactere") == 0) {
        CutLines(loadedImage);
        window = display_img(loadedImage);
        wait_for_keypressed();
    }

      if (strcmp(argv[1], "RLSAv") == 0) {
        blockDetection_vertical(loadedImage);
        window = display_img(loadedImage);
        wait_for_keypressed();
    }

     if (strcmp(argv[1], "binerize") == 0) {
        binerize(loadedImage);
        window = display_img(loadedImage);
        wait_for_keypressed();
    }

       if (strcmp(argv[1], "RLSAh") == 0) {
        blockDetection_horizontal(loadedImage);
        window = display_img(loadedImage);
        wait_for_keypressed();
    }


    SDL_SaveBMP(loadedImage,"src/final12.bmp");

    SDL_FreeSurface(loadedImage);

    return 0;
}
#include "Filter/cleanerimage.h"
#include "Segmentation/segmentation.h"
#include <string.h>
#include "display.h"
#include "SDL2/SDL_image.h"


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

    /*binerize(loadedImage);

    int* r = histo(loadedImage);

    for (int i = 0; i < loadedImage -> w; i++)
    {
        printf("%i \n", r[i]);
    }*/

    display_img(loadedImage);

    wait_for_keypressed();


    if (!loadedImage)
    {
        printf("Can't find the bmp file\n");
        return 1;
    }

    if (strcmp(argv[1], "grayscale") == 0) {
        grayscale(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        ConstrastRenforcement(loadedImage,100);
        display_img(loadedImage);
        wait_for_keypressed();
    }

    if (strcmp(argv[1], "contrast") == 0) {
        ConstrastRenforcement(loadedImage,100);
        display_img(loadedImage);
        wait_for_keypressed();
    }

    if (strcmp(argv[1], "removenoise") == 0) {
        noiseReduction(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
    }

    if (strcmp(argv[1], "CutCharactere") == 0) {
        CutLines(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
    }

      if (strcmp(argv[1], "block") == 0) {
        grayscale(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        binerize(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        SDL_Surface *imagev = copy_image(loadedImage);
        SDL_Surface *imagerlsa = copy_image(loadedImage);
        blockDetection_vertical(imagev);
        wait_for_keypressed();
        drawBlocks(imagerlsa,imagev);
        display_img(imagerlsa);
        drawBlocksLines(loadedImage, imagerlsa);
        display_img(loadedImage);
        wait_for_keypressed();
    }

     if (strcmp(argv[1], "binerize") == 0) {
        binerize(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
    }

       if (strcmp(argv[1], "RLSAh") == 0) {
        blockDetection_horizontal(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
    }
       if (strcmp(argv[1], "C") == 0) {
        loadedImage=resize(loadedImage,1218,41);
        grayscale(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        binerize(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        cutword(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
    }


    SDL_SaveBMP(loadedImage,"src/final12.bmp");

    SDL_FreeSurface(loadedImage);

    return 0;
}
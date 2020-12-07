#include "Filter/cleanerimage.h"
#include "Segmentation/segmentation.h"
#include "extraction/extraction.h"
#include "extraction/extractchar.h"
#include <string.h>
#include "display.h"
#include "SDL2/SDL_image.h"


int main(int argc, char *argv[])
{

    if (argc == 1)
    {
        printf("Welcome to our Image treatment.\n The following command are avaible :  \n -grayscale \n -binerize \n -cutchar \n -RLSAh \n -RLSAv \n -contrast \n -block \n");
        return 1;
    }
    if (argc < 3) {
		printf("Error, two arguments needed.\n");
		return 1;
	}

    SDL_Surface *loadedImage = 0;
    loadedImage = SDL_LoadBMP(argv[2]);
    //display_img(loadedImage);
    //wait_for_keypressed();

    if (!loadedImage)
    {
        printf("Can't find the bmp file\n");
        return 1;
    }

    if(strcmp(argv[1], "extract") == 0)
    {
        //grayscale(loadedImage);
        binerize(loadedImage);
        
        __extractpar(loadedImage);
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

    if (strcmp(argv[1], "resize") == 0) {
        binerize(loadedImage);

        
    }

    if (strcmp(argv[1], "removenoise") == 0) {
        //binerize(loadedImage);
        noiseReduction(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
    }

     if (strcmp(argv[1], "rotate") == 0) {
        grayscale(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        binerize(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        double teta = houghtrasformy(loadedImage);

        if (teta > 90)
        {
            teta+=90;
        }
        else
        {
            teta-=90;
        }
        
        
        display_img(rotate(teta,loadedImage));
        wait_for_keypressed();
    }

     if (strcmp(argv[1], "cutline") == 0) {
        binerize(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        grayscale(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        CutLines(loadedImage, 0);
        display_img(loadedImage);
        wait_for_keypressed();
    }

    if (strcmp(argv[1], "cutcar") == 0) {
        binerize(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        grayscale(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        CutLines(loadedImage, 1);
        display_img(loadedImage);
        wait_for_keypressed();
    }

       if (strcmp(argv[1], "cutcar2") == 0) {
        binerize(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
        cutchar(loadedImage);
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
        SDL_FreeSurface(imagev);
        SDL_FreeSurface(imagerlsa);

    }

     if (strcmp(argv[1], "binerize") == 0) {
        binerize(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
    }

       if (strcmp(argv[1], "RLSAh") == 0) {
        binerize(loadedImage);
        blockDetection_horizontalv2(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
    }

    if (strcmp(argv[1], "RLSAv") == 0) {
        blockDetection_vertical(loadedImage);
        display_img(loadedImage);
        wait_for_keypressed();
    }
    if (strcmp(argv[1], "cutword2") == 0) {
        binerize(loadedImage);
        __extractchar(loadedImage);

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

    SDL_SaveBMP(loadedImage,"src/resize.bmp");
    SDL_FreeSurface(loadedImage);

    return 0;
}
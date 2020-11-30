#include "extraction.h"
#include "../display.h"

int countlinepar(SDL_Surface* img)
{
    int h = img -> h; 
    Uint32 pixel = 0;
    Uint8 r, g, b;
    int count = 0;

    for (int i = 0; i < h; i++)
    {
        
        pixel = getpixel(img,1,i);
        SDL_GetRGB(pixel, img->format, &r, &g, &b);
        if ((r== 0 && g == 0 && b == 255) || (r == 255 && g == 150 && b == 255))
        {
            printf("r : %i, g : %i, b: %i, y = %i\n",r,g,b,i);
            count++;
        }
    }
    return count;
    
}

void ReturnPosPar(SDL_Surface* img, int *tab)
{
    int h = img -> h; 
    Uint32 pixel = 0;
    Uint8 r, g, b;
    int count = 0;

    for (int i = 0; i < h; i++)
    {
        pixel = getpixel(img,1,i);
        SDL_GetRGB(pixel, img->format, &r, &g, &b);
        if ((r== 0 && g == 0 && b == 255) || (r == 255 && g == 150 && b == 255))
        {
            tab[count]= i;
            count++;
        }
    }
}


void extractpar(SDL_Surface* img,int x, int y)
{
    SDL_Surface* new = CreateWhiteSurface(img->w,y-x+1, img);
    Uint32 pixel = 0;
    
    for (int i = 0; i < img -> w ; i++)
    {
        for (int j = x+1; j < y; j++)
        {
            pixel = getpixel(img, i, j);
            putpixel(new, i, j-x, pixel);
        }
        
    }

    SDL_SaveBMP(new,"final12.bmp");
    display_img(new);

    wait_for_keypressed();
    __extractline(new);
    SDL_FreeSurface(new);
}

void __extractpar(SDL_Surface* img)
{
    SDL_Surface *imagev = copy_image(img);
    SDL_Surface *imagerlsa = copy_image(img);
    SDL_Surface *copy_image1 = copy_image(img);
    display_img(copy_image1);

    wait_for_keypressed();

    blockDetection_vertical(imagev);
    drawBlocks(imagerlsa,imagev);
    drawBlocksLines(copy_image1, imagerlsa);

    display_img(copy_image1);

    wait_for_keypressed();



    int count = countlinepar(copy_image1);

   // printf("count : %i\n", count);

    int *tab = malloc(sizeof(int)*count);

    ReturnPosPar(copy_image1, tab);

    for (int i = 0; i < count; i+=2)
    {
        printf("coord : %i, %i\n", tab[i],tab[i+1]);
        extractpar(copy_image1, tab[i], tab[i+1]);       

    }
    SDL_FreeSurface(imagerlsa);
    SDL_FreeSurface(imagev);
    SDL_FreeSurface(copy_image1);
    free(tab);

}



void extractline(SDL_Surface *img, int x, int y)
{
    SDL_Surface* new = CreateWhiteSurface(img->w,y-x+1, img);
    Uint32 pixel = 0;
    
    for (int i = 0; i < img -> w ; i++)
    {
        for (int j = x+1; j < y; j++)
        {
            pixel = getpixel(img, i, j);
            putpixel(new, i, j-x, pixel);
        }
        
    }
    display_img(new);

    wait_for_keypressed();

    SDL_SaveBMP(new,"final13.bmp");
}

void __extractline(SDL_Surface *img)
{

    SDL_Surface* copy = copy_image(img);
    CutLines(copy, 0);

    display_img(copy);

    wait_for_keypressed();
    int count = countlinepar(copy);
    int *tab = malloc(sizeof(int)*count);
    ReturnPosPar(copy, tab);
    for (int i = 0; i < count; i+=2)
    {
        printf("coord : %i, %i\n", tab[i],tab[i+1]);
        extractline(copy, tab[i], tab[i+1]);       

    }

    SDL_FreeSurface(copy);
    free(tab);

}


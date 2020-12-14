#include "extraction.h"
#include "extractchar.h"
#include "../display.h"
#include "../Segmentation/segmentation.h"
#include <string.h>


/*
Count the number of line and paragraph in the current image
*/
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
            count++;
        }
    }

    return count;
}

/*
Fill an array with the position of line and paragraph
*/
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

/*
Create a new surface and paragraph for line segmentation
*/
void extractpar(SDL_Surface* img,int x, int y,Neural_Network *network, char *str)
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

    __extractline(new,network,str);
    SDL_FreeSurface(new);
}

void __extractpar(SDL_Surface* img,Neural_Network *network, char *str)
{
    SDL_Surface *imagev = copy_image(img);
    SDL_Surface *imagerlsa = copy_image(img);
    SDL_Surface *copy_image1 = copy_image(img);
    blockDetection_vertical(imagev);
    drawBlocks(imagerlsa,imagev);
    drawBlocksLines(copy_image1, imagerlsa);
    int count = countlinepar(copy_image1);
    int *tab = malloc(sizeof(int)*count);
    ReturnPosPar(copy_image1, tab);

    for (int i = 0; i < count; i+=2)
    {
        extractpar(copy_image1, tab[i], tab[i+1],network,str); 
        char a[] = "\n\n\n";
        strcat(str,a);      
    }

    SDL_FreeSurface(imagerlsa);
    SDL_FreeSurface(imagev);
    SDL_FreeSurface(copy_image1);
    free(tab);
}

/*
Create a new surface and extract the line for word segmentation
*/
void extractline(SDL_Surface *img, int x, int y,Neural_Network *network, char *str)
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

    __extractword(new,network,str);
    SDL_FreeSurface(new);
}

void __extractline(SDL_Surface *img,Neural_Network *network, char *str)
{
    SDL_Surface* copy = copy_image(img);
    CutLines(copy, 0);
    int count = countlinepar(copy);
    int *tab = malloc(sizeof(int)*count);
    ReturnPosPar(copy, tab);

    for (int i = 0; i < count; i+=2)
    {
        extractline(copy, tab[i], tab[i+1],network,str); 
        char a[]="\n";
        strcat(str,a);         
    }

    SDL_FreeSurface(copy);
    free(tab);
}


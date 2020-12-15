#include "extractchar.h"
#include "../display.h"
#include <string.h>

/*
Return the number of word in the current image
*/
int countwc(SDL_Surface* img)
{
    int w = img -> w; 
    Uint32 pixel = 0;
    Uint8 r, g, b;
    int count = 0;

    for (int i = 0; i < w; i++)
    {  
        pixel = getpixel(img,i,1);
        SDL_GetRGB(pixel, img->format, &r, &g, &b);
        if ((r== 1 && g == 100 && b == 100))
        {
            count++;
        }
    }

    return count;
}

/*
Return an array of the position of words in the current image
*/
void ReturnPoswc(SDL_Surface* img, int *tab)
{
    int w = img -> w; 
    Uint32 pixel = 0;
    Uint8 r, g, b;
    int count = 0;

    for (int i = 0; i < w; i++)
    {
        pixel = getpixel(img,i,1);
        SDL_GetRGB(pixel, img->format, &r, &g, &b);
        if ((r== 1 && g == 100 && b == 100))
        {
            tab[count]= i;
            count++;
        }
    }
}

/*
Create a new surface and extract the word for charactere segmentation
*/
void extractword(SDL_Surface* img,int x, int y,
                Neural_Network *network,char *str)
{ 
    SDL_Surface* new = CreateWhiteSurface(y-x+1,img->h, img);
    Uint32 pixel = 0;
    
    for (int i = x+1; i < y ; i++)
    {
        for (int j = 0; j < img->h; j++)
        {
            pixel = getpixel(img, i, j);
            putpixel(new, i-x, j, pixel);
        }
        
    }

    SDL_SaveBMP(new,"final12.bmp");
    __extractchar(new,network,str);
    SDL_FreeSurface(new);
}


/*
Create a new surface and extract the caracters for neural network
*/
void __extractword(SDL_Surface* img,Neural_Network *network,char *str)
{
    SDL_Surface* loadedImage=resize(img,1218,41);
    cutword(loadedImage);
    int count = countwc(loadedImage);
    int *tab = malloc(sizeof(int)*count);
    ReturnPoswc(loadedImage, tab);

    for (int i = 0; i < count-1; i+=1)
    {
        extractword(loadedImage, tab[i], tab[i+1],network,str);
        char a[]=" ";
        strcat(str,a);          
    }

    SDL_FreeSurface(loadedImage);
    free(tab);
}

int fullofwhite(SDL_Surface * img)
{
    Uint32 pixel = 0;
    Uint8 r, g, b;

    for (int i = 0; i < img->h; i++)
    {
        for (int  j = 0; j <  img->w ; j++)
        {
            pixel = getpixel(img,j,i);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if (r ==0 && g==0 && b == 0)
            {
                return 1;
            }
        }
        
    }
    
    return 0;
}

void extractchar(SDL_Surface* img,int x, int y,Neural_Network *network,char *str)
{
    SDL_Surface* new = CreateWhiteSurface(y-x+1,img->h, img);
    Uint32 pixel = 0;
    
    for (int i = x+1; i < y ; i++)
    {
        for (int j = 0; j < img->h; j++)
        {
            pixel = getpixel(img, i, j);
            putpixel(new, i-x, j, pixel);
        }
        
    }
    if (fullofwhite(new))
    {
        ForwardPass(segmentationtomatrix(new, 20), network);
        char a[2];
        a[0] = indiceToChar(network->output);
        a[1]='\0';
        strcat(str,a);          
    }
}

void __extractchar(SDL_Surface* img,Neural_Network *network,char *str)
{
    SDL_Surface* loadedImage=copy_image(img);
    CutColumn(loadedImage,0,img->h);
    int count = countwc(loadedImage);
    int *tab = malloc(sizeof(int)*count);
    ReturnPoswc(loadedImage, tab);

    for (int i = 0; i < count-1; i+=1)
    {
        extractchar(loadedImage, tab[i], tab[i+1],network, str);       
    }

    SDL_FreeSurface(loadedImage);
    free(tab);
}
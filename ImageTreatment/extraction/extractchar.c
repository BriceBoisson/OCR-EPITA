#include "extractchar.h"
#include "../display.h"
#include <string.h>

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
            //printf("word r : %i, g : %i, b: %i, y = %i\n",r,g,b,i);
            count++;
        }
    }
    return count;
    
}

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

void extractword(SDL_Surface* img,int x, int y,Neural_Network *network,char *str)
{ 
    SDL_Surface* new = CreateWhiteSurface(y-x+1,img->h, img);
    Uint32 pixel;
    
    for (int i = x+1; i < y ; i++)
    {
        for (int j = 0; j < img->h; j++)
        {
            pixel = getpixel(img, i, j);
            putpixel(new, i-x, j, pixel);
        }
        
    }


    SDL_SaveBMP(new,"final12.bmp");
    //display_img(new);

    //wait_for_keypressed();
    __extractchar(new,network,str);
    SDL_FreeSurface(new);
}

void __extractword(SDL_Surface* img,Neural_Network *network,char *str)
{
    SDL_Surface* loadedImage=resize(img,1218,41);
    //display_img(loadedImage);
   // wait_for_keypressed();
    cutword(loadedImage);
    //display_img(loadedImage);
    //wait_for_keypressed();
    int count = countwc(loadedImage);
   // printf("count word : %i\n", count);
   // printf("count : %i\n", count);
    int *tab = malloc(sizeof(int)*count);
    ReturnPoswc(loadedImage, tab);

    for (int i = 0; i < count-1; i+=1)
    {
        //printf("coord word : %i, %i\n", tab[i],tab[i+1]);
        extractword(loadedImage, tab[i], tab[i+1],network,str);
        char a[1];
        a[0] =' ';
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
        //SDL_SaveBMP(new,"final12.bmp");
       // display_img(new);//PERMET D'AFFICHER UNE IMAGE, ICI LE CARACTERE DECOUPE (utile pour débugger) Tu peux les retirer dans les fonctions
        /* ICI ON A UN CARACTERE DECOUPE QUE LON PEUT ENVOYER AU RESEAU*/
        //wait_for_keypressed();//PERMET DE FAIRE UNE PAUSE et DATTENDRE LAPPUIE SUR UNE TOUCHE 
        ForwardPass(segmentationtomatrix(new, 20), network);
        char a[2];
        a[0] = indiceToChar(network->output);
        a[1]='\0';

        //printf("CHAR DETECT : %s",a);
        strcat(str,a);   
        
        //SDL_FreeSurface(new);

    }

}

void __extractchar(SDL_Surface* img,Neural_Network *network,char *str)
{
   SDL_Surface* loadedImage=copy_image(img);
    //display_img(loadedImage);

   // wait_for_keypressed();

    CutColumn(loadedImage,0,img->h);

    //display_img(loadedImage);

   // wait_for_keypressed();



    int count = countwc(loadedImage);

   // printf("count : %i\n", count);

    int *tab = malloc(sizeof(int)*count);

    ReturnPoswc(loadedImage, tab);

    for (int i = 0; i < count-1; i+=1)
    {
        //printf("coord char : %i, %i\n", tab[i],tab[i+1]);
        extractchar(loadedImage, tab[i], tab[i+1],network, str);       

    }
    SDL_FreeSurface(loadedImage);
    free(tab);
}
#include "cleanerimage.h"





void grayscale(SDL_Surface *img)
{
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int w = img -> w;
    int h = img -> h;

    for (int i = 0; i < w;i++)
    {
        for(int j = 0; j< h; j++)
        {
            pixel = getpixel(img, i,j);
            SDL_GetRGB(pixel, img->format, &r,&g,&b);
            /*maybe change this value*/
            Uint8 results = 0.3*r + 0.59*g + 0.11*b;
            pixel = SDL_MapRGB(img -> format,results,results,results);
            putpixel(img,i,j,pixel);
        }
    }
}

void binerize(SDL_Surface *img)
{
  /* Variables */
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int w = img -> w;
  int h = img -> h;
  
 for(int i = 0; i < w; i++)
 {
   for(int j = 0; j < h; j++)
   {
     pixel = getpixel(img,i,j);
     SDL_GetRGB(pixel, img->format, &r, &g, &b);

     Uint32 average = (r+b+g) /3;

     

    
     if(average > 150) /*we can make an average here*/
     {
      r = 255;
      g = 255;
      b = 255;
     }
     else
     {
      r = 0;
      g = 0;
      b = 0;
     }
     pixel = SDL_MapRGB(img->format, r, g, b);
     putpixel(img, i, j, pixel);
   }
 }

}


void noiseReduction(SDL_Surface *img)
{
  /* Variables */
  int w;
  int h;
  w = img -> w;
  h = img -> h;
  int pixelmap[5];

 for(int i = 0; i < w; i++)
 {
   for(int j = 0; j < h; j++)
   {
     for(int k = j; k <= j ; k++)
     {
       
       if(i == 0)
       {
         if(k == 0)
         {
            pixelmap[0] = getpixel(img, i, k);
            pixelmap[1] = getpixel(img, i, k);
            pixelmap[2] = getpixel(img, i, k);
            pixelmap[3] = getpixel(img, i, k + 1);
            pixelmap[4] = getpixel(img, i + 1, k);
            break;
         }
         if(k == h)
         {
            pixelmap[0] = getpixel(img, i, k);
            pixelmap[1] = getpixel(img, i, k - 1);
            pixelmap[2] = getpixel(img, i, k);
            pixelmap[3] = getpixel(img, i, k);
            pixelmap[4] = getpixel(img, i + 1, k);
            break;
         }
         else
         {
          pixelmap[0] = getpixel(img, i, k);
          pixelmap[1] = getpixel(img, i, k - 1);
          pixelmap[2] = getpixel(img, i, k);
          pixelmap[3] = getpixel(img, i, k + 1);
          pixelmap[4] = getpixel(img, i + 1, k);
          break;
         }
       }
       if(i == w)
       {
          if(k == 0)
          {
            pixelmap[0] = getpixel(img, i, k);
            pixelmap[1] = getpixel(img, i, k);
            pixelmap[2] = getpixel(img, i - 1, k);
            pixelmap[3] = getpixel(img, i, k + 1);
            pixelmap[4] = getpixel(img, i, k);
            break;
          }
          if(k == h)
          {
            pixelmap[0] = getpixel(img, i, k);
            pixelmap[1] = getpixel(img, i, k - 1);
            pixelmap[2] = getpixel(img, i - 1, k);
            pixelmap[3] = getpixel(img, i, k);
            pixelmap[4] = getpixel(img, i, k);
            break;
          }
          else
          {
            pixelmap[0] = getpixel(img, i, k);
            pixelmap[1] = getpixel(img, i, k - 1);
            pixelmap[2] = getpixel(img, i - 1, k);
            pixelmap[3] = getpixel(img, i, k + 1);
            pixelmap[4] = getpixel(img, i, k);
            break;
          }
       }
       if(k == 0)
       {
          pixelmap[0] = getpixel(img, i, k);
          pixelmap[1] = getpixel(img, i, k);
          pixelmap[2] = getpixel(img, i - 1, k);
          pixelmap[3] = getpixel(img, i, k + 1);
          pixelmap[4] = getpixel(img, i + 1, k);
          break;
       }
       if(k == h)
       {
        pixelmap[0] = getpixel(img, i, k);
        pixelmap[1] = getpixel(img, i, k - 1);
        pixelmap[2] = getpixel(img, i - 1, k);
        pixelmap[3] = getpixel(img, i, k);
        pixelmap[4] = getpixel(img, i + 1, k);
        break;
       }
       else
       {
        pixelmap[0] = getpixel(img, i, k);
        pixelmap[1] = getpixel(img, i, k - 1);
        pixelmap[2] = getpixel(img, i - 1, k);
        pixelmap[3] = getpixel(img, i, k + 1);
        pixelmap[4] = getpixel(img, i + 1, k);
        break;
       }
     }
      array_select_sort(pixelmap, 5);
      int med = pixelmap[2];
      putpixel(img, i, j, med);
   }
 }
}




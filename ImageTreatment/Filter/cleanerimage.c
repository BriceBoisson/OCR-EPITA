#include "cleanerimage.h"
#include "../display.h"






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
int IsValid(int x, int y, int w, int h)
{
  return x >= 0 && x < w && y >= 0 && y < h;
}

SDL_Surface* Convolute(SDL_Surface* img, float mask[3][3])
{
  int offset = 3/ 2;
  Uint8 r,g,b;
  Uint32 pixel = 0;
  SDL_Surface* copy = CreateWhiteSurface(img->w,img->h,img);
  for (int y = 0; y < img->h; ++y)
  {
    printf("test\n");
      for (int x = 0; x < img->w; ++x)
      {
        printf("test1\n");
        float red = 0;
        float green = 0;
        float blue = 0;
        for (int dy = -offset; dy <= offset; ++dy)
        {
          printf("test2\n");
            for (int dx = -offset; dx <= offset; ++dx)
            {
              printf("test3\n");
                if (IsValid(x + dx, y + dy, img->w,img->h))
                {
                  printf("dx + x = %i, dy + y = %i, w : %i, h : %i \n",dx + x,dy + y,img->w,img->h);
                  pixel = getpixel(img,x + dx, y + dy);
                  float coefficient = mask[dy + offset][dx + offset];
                  SDL_GetRGB(pixel, img->format, &r, &g, &b);
                  red += r * coefficient;
                  green += g * coefficient;
                  blue += b * coefficient;
                }
            }
        }
        printf("r = %i, g = %i, b : %i \n",Restrict256(red),Restrict256(green),Restrict256(blue));
        pixel = SDL_MapRGB(img->format,Restrict256(red), Restrict256(green), Restrict256(blue));
        putpixel(copy,x, y, pixel);
      }
  }
  /*for (int k = 0; k < img->h; k++)
  {
    for (int c = 0; c < img->w; c++)
    {
      pixel = SDL_MapRGB(img->format,100,100,100);
      putpixel(copy,c,k,pixel);
    }
    
  }*/
  
  /*display_img(copy);
  wait_for_keypressed();*/
  return copy;
}

int Restrict256(int n)
{
  if (n < 0)
    return 0;
  if (n > 255)
    return 255;
  return n;
}

void ConstrastRenforcement(SDL_Surface* img,int delta)
{
  double factor = (259 * (delta + 255)) / (255.0 * (259.0 - delta));
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int w = img -> w;
  int h = img -> h;

  if (delta == 259)
  {
    delta = 258;
  }
    
    for (int i = 0; i < w;i++)
    {
        for(int j = 0; j< h; j++)
        {
            pixel = getpixel(img, i,j);
            SDL_GetRGB(pixel, img->format, &r,&g,&b);
            r = Restrict256(factor * (r - 128) + 128);
            g = Restrict256(factor * (g- 128) + 128);
            b = Restrict256(factor * (b - 128) + 128);
            pixel = SDL_MapRGB(img -> format,r,g,b);
            putpixel(img,i,j,pixel);
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
  int pixelmap[9];

 for(int i = 1; i < h-1; i++)
 {
   for(int j = 1; j < w-1; j++)
   {

     pixelmap[0] = getpixel(img,j-1,i-1);
     pixelmap[1] = getpixel(img,j, i-1);
     pixelmap[2] = getpixel(img,j+1,i-1);
     pixelmap[3] = getpixel(img, j-1,i);
     pixelmap[4] = getpixel(img,j,i);
     pixelmap[5] = getpixel(img,j+1,i);
     pixelmap[6] = getpixel(img,j-1, i+1);
     pixelmap[7] = getpixel(img,j,i+1 );
     pixelmap[8] = getpixel(img,j+1,i+1 );


     
      array_select_sort(pixelmap, 9);
      int med = pixelmap[4];
      putpixel(img, j, i, med);
   }
 }
}




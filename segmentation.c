#include "segmentation.h"


/*find if a line contain black pixel*/
int FindBlackPixel(SDL_Surface *img, int x)
{
  Uint32 pixel;
  int w;
  int h;
  Uint8 r, g, b;
  int bool = 1; /*A boolean that memorize if the line contain black pixel or not*/
  w = img -> w;
  h = img -> h;

  for(int i = 0; i < w; i++)
 {
    pixel = getpixel(img,i,x);
    SDL_GetRGB(pixel, img->format, &r, &g, &b);

    if (r == 0)
    {
        bool = 0;
        break;
    }
 }

 return bool;
}

void CutLines(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int w, h;
  int end_line =0;
  int begin_line=0;
  w = img -> w;
  h = img -> h;

  for(int i = 0; i < h; i++)
 {
     
     for (int j = 0; j< w; j++)
     {
         pixel = getpixel(img,j,i);
         SDL_GetRGB(pixel, img->format, &r, &g, &b);
         
         if (r == 0) /*after binerize is not necessary to test the others values */
            {
                if (FindBlackPixel(img,i-1))/*For the first black pixel we meet, we check if the upper line is full of white and then we draw a line for mark the begin of a new line*/
                {
                    DrawALine(img,i-1);
                    begin_line=i-1;
                }

                if (FindBlackPixel(img, i+1)) /*same but for the under line*/
                {
                    DrawALine(img,i+1);
                    end_line =i+1;
                }

                if (end_line && begin_line)
                {
                    CutColumn(img, begin_line,end_line);

                    end_line=0;
                    begin_line=0;
                }
                break;
            }
     }
 }
}


/*draw a line if necessary*/
void DrawALine(SDL_Surface *img,int x) 
{
  Uint32 pixel;
  int w;
  int h;
  w = img -> w;

  for(int i = 0; i < w; i++)
 {
     pixel = SDL_MapRGB(img->format, 255, 150, 255);
     putpixel(img, i, x, pixel);
 }
}


void CutColumn(SDL_Surface * img, int begin_line, int end_line)
{
    Uint8 r, g, b;
    Uint32 pixel;
    int w = img -> w;
    for (int i = 0; i < w ; i++)
    {
        for (int j = begin_line;j< end_line;j++)
        {
            pixel = getpixel(img,i,j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if (r == 0) /*after binerize is not necessary to test the others values */
            {
                if (FindBlackPixelInColumn(img, begin_line,end_line,i-1))/*For the first black pixel we meet, we check if the upper line is full of white and then we draw a line for mark the begin of a new line*/
                {
                    DrawAColumn(img,i-1,begin_line,end_line);
                    
                }

                if (FindBlackPixelInColumn(img, begin_line,end_line,i+1)) /*same but for the under line*/
                {
                    DrawAColumn(img,i+1,begin_line,end_line);
                    
                }
                break;
            }

        }

    }
}


int FindBlackPixelInColumn(SDL_Surface *img, int begin_line, int end_line, int start)
{
  Uint32 pixel;
  int w;
  int h;
  Uint8 r, g, b;
  int bool = 1; /*A boolean that memorize if the line contain black pixel or not*/

  for(int i = begin_line; i < end_line; i++)
 {
    pixel = getpixel(img,start,i);

    SDL_GetRGB(pixel, img->format, &r, &g, &b);

    if (r == 0)
    {
        bool = 0;
        break;
    }
 }

 return bool;
}


/*Draw a column between two lines and characters*/

void DrawAColumn(SDL_Surface *img,int y, int x, int end_line)
{
    Uint32 pixel;
    Uint32 pixel2;
    Uint8 r, g, b;
    
  for(int i = x; i < end_line; i++)
 { 
    SDL_GetRGB(pixel2, img->format, &r, &g, &b);

    if (r == 255 && g == 150 && b == 255 )
    {
        break;
    }
    else
    {
        pixel = SDL_MapRGB(img->format, 255, 255, 0);
        putpixel(img, y, i, pixel);
    }
    
 }
}

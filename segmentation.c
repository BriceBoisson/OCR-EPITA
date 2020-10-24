# include "segmentation.h"

/*  FRENCH: la normalement tout marche mais je peux pas tester j'ai que dalle sur mon pc
    et y'a des trucs a tester avec un reseau de neurones mais pour la 1e soutenance on
    est en avance.
    Ca coupe les lignes et colonnes comme tu faisais deja mais la dcp y'a les espaces en
    plus
    Je v voir l'algo du RLSA pour detecter les blocks pcq c'est ce que les anciens
    avaient fait et apparemment c'est le meilleur algo pour ca mais ce sera pas pour
    cette soutenance a moins que j'ai vraiment bcp bcp de temps libre mdrr
*/


/* Cut the lines of the image */
SDL_Surface* lineCut(SDL_Surface *img)
{
    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int isBlank = 1;
    int firstCut = 1;
    SDL_Surface *img_copy = copy_image(img);
    for(int i = 0; i < (img_copy -> h) ; i++)
    {
      isBlank = 1 ;
      for(int j = 0 ; j < (img_copy -> w); j++)
      {
        pixel = getpixel(img, j, i);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);
        //Check if there is a black character in this line
        if(!r && !g && !b)
        {
          isBlank = 0;
          break;
        }
      }
      //For the first cut we cut the pixel line
      //before the line with a black character
      if(!isBlank && firstCut)
      {
          for(int k = 0; k < (img_copy -> w); k++)
          {
            pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
            putpixel(img_copy, k, i - 1, pixel);
          }
          firstCut = 0;
      }
      //For the second cut we cut the first white line
      if(isBlank && !firstCut)
      {
        for(int k = 0; k < (img_copy -> w); k++)
        {
          pixel = SDL_MapRGB(img_copy -> format, 255, 0, 0);
          putpixel(img_copy, k, i, pixel);
        }
        firstCut = 1;
      }
    }
    return(img_copy);
}
/* Isolate the lines */
void isolateLine(SDL_Surface *img, struct Neural_Network *net)
{
  /* Variables */
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int firstCut;
  int lastCut = 0;

  for(int i = 0; i < (img -> h); i++)
  {
    if(i != 0 && i <= lastCut)
    {
      continue;
    }
    pixel = getpixel(img, 0, i);
    SDL_GetRGB(pixel, img -> format, &r, &g, &b);
    //If there is a red line start cut
    if(r == 255 && b == 0 && g == 0)
    {
      firstCut = i + 1;

      for(int j = firstCut + 1; j < (img -> h); j++)
      {
        pixel = getpixel(img, 0, j);
        SDL_GetRGB(pixel, img -> format, &r, &g, &b);

        //Detect the second line
        if(r == 255 && b==0 && g == 0)
        {
          lastCut = j;
          //Isolate into a surface the linecut
          cuttedSurface(img, firstCut, lastCut, net);
          break;
        }
      }
    }
  }
}
/* Display the isolated cuts */
void cuttedSurface(SDL_Surface *img, int firstCut,
                  int lastCut, struct Neural_Network *net)
{
  /* Variables */
  Uint32 pixel;
  SDL_Surface* copy = NULL;

  //Create a surface that contain the cutting zone
  copy = SDL_CreateRGBSurface(SDL_HWSURFACE,
                              img -> w,
                              lastCut - firstCut,
                              img -> format -> BitsPerPixel, 0, 0, 0, 0);
  //Copy the cutting zone into the new surface
  for(int i = 0; i < copy -> w; i++)
  {
    for(int j = 0; j < copy -> h; j++)
    {
      pixel = getpixel(img, i, firstCut + j);
      putpixel(copy, i, j, pixel);
    }
  }
  //Cut the characters
  charCut(copy);
  isolateChar(copy, net);
  net -> str = concat(net -> str, "\n");
}

/* Cut the characters into the isolated cuts */
void charCut(SDL_Surface *img)
{
  // Variables
  Uint32 pixel;
  Uint8 r ;
  Uint8 g;
  Uint8 b;
  int thereIsChar = 0;
  int lineWasWhite = 1;
  int canCut = 0;

  for(int i = 0; i < img -> w; i++)
  {
    lineWasWhite = 1;
    for(int j = 0; j < img -> h; j++)
    {
      pixel = getpixel(img, i, j);
      SDL_GetRGB(pixel, img -> format, &r, &g, &b);
      if(r == 0 && g == 0 && b == 0)
      {
          thereIsChar = 1;
          lineWasWhite = 0;
          break;
      }
    }
    if(lineWasWhite && !canCut)
    {
      continue;
    }
    if(thereIsChar && !canCut)
    {
      for(int k = 0; k < img -> h; k++)
      {
        pixel = SDL_MapRGB(img -> format, 255, 0, 0);
        putpixel(img, i - 1, k, pixel);
      }
      canCut = 1;
    }
    if(lineWasWhite && canCut)
    {
      for(int k = 0; k < img -> h; k++)
      {
        pixel = SDL_MapRGB(img -> format, 255, 0, 0);
        putpixel(img, i, k, pixel);
      }
      canCut = 0;
    }

  }
}

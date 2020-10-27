#include "segmentation.h"



    // DECOUPAGE DES BLOCS


// renvoie la moyenne d'espacement entre les pixels noir pour avoir une idee de l'espacement des blocs
int pixelSpacingHorizontal(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int white = 0;
  int black = 0;

  for(int i = 0; i < img -> h; i++)
  {
    for(int j = 0; j < img -> w; j++)
    {
      pixel = getpixel(img, j, i);
      SDL_GetRGB(pixel, img -> format, &r, &g, &b);    // recup les r g b du pixel en cours (j, i) car on est en horizontal
      if(r == 255 && g == 255 && b == 255)    // incremente white ou black selon qu'il est noir ou blanc
      {white++;}
      else
      {black++;}
    }

  }
  return (white / (black / 2));    // renvoie la moyenne ( nombre de blanc / (nombre de noirs / 2)  )
}

// fonctionne pareil que la version horizontale
int pixelSpacingVertical(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int white = 0;
  int black = 0;

  for(int i = 0; i < img -> w; i++)
  {
    for(int j = 0; j < img -> h; j++)
    {
      pixel = getpixel(img, i, j);
      SDL_GetRGB(pixel, img -> format, &r, &g, &b);    // recup les r g b du pixel (i, j) car vertical
      if(r == 255 && g == 255 && b == 255)    // pareil qu'en version horizontal
      {white++;}
      else
      {black++;}
    }
  }
  return(white / (black / 2));    //pareil qu'en horizontal
}


// RLSA

// remplis les espaces horizontaux entre deux blocs en noir
void blockDetection_horizontal(SDL_Surface *img)
{ 
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int hori = pixelSpacingHorizontal(img)*4;    // c'est une moyenne de l'espacement, pour avoir un seuil adapté a l'image et pas reunir deux blocs entre eux par erreur
  int countWhite;

  for(int i = 0; i < img -> h; i++)
  {
    countWhite = 0;
    for(int j = 0; j < img -> w; j++)
    {
      pixel = getpixel(img, j, i);
      SDL_GetRGB(pixel, img -> format, &r, &g, &b);    // on recup le rgb de (j, i) car horitzontal
      if(r == 255 && g == 255 && b == 255)    // on ajoute un blanc au compteur si le pixel est blanc
      {
        countWhite++;
      }
      if(r == 0 && g == 0 && b == 0)    // sinon on compare le nombre de pixels blancs entre les deux pixels noirs avec hori
      {
        if(countWhite <= hori)    // si c'est inferieur on rempli l'espace de noir pour creer le bloc
        {
            int k = j - 1;
            while(countWhite > 0)
            {
              pixel = SDL_MapRGB(img -> format, 0, 0, 0);
              putpixel(img, k, i, pixel);
              countWhite--;
              k--;
            }
        }
        else    // sinon on a deux blocs separes donc il ne faut pas remplir l'espace
        {
          countWhite = 0;
        }
      }
    }
  }
}

// remplis les espaces verticaux entre deux blocs. fonctionne pareil que la version horizontale
void blockDetection_vertical(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int verti = pixelSpacingVertical(img) * 4;
  int countBlack;

  for(int i = 0; i < img -> w; i++)
  {
    countBlack = 0;
    for(int j = 0; j < img -> h; j++)
    {
      pixel = getpixel(img, i, j);
      SDL_GetRGB(pixel, img -> format, &r, &g, &b);
      if(r == 255 && g == 255 && b == 255)
      {
        countBlack++;
      }
      else
      {
        if(countBlack <= verti)
        {
            int k = j - 1;
            while(countBlack > 0)
            {
              pixel = SDL_MapRGB(img -> format, 0, 0, 0);
              putpixel(img, i, k, pixel);
              countBlack--;
              k--;
            }
        }
        else
        {
          countBlack = 0;
        }
      }
    }
  }
}



// Trace les lignes des blocs avec le RLSA
void drawBlocksLines (SDL_Surface *img, SDL_Surface *imgRLSA)
{
  Uint32 pixel;
  Uint32 pixelRLSA;
  Uint32 pixelUp;
  Uint32 pixelDown;
  Uint32 pixelLeft;
  Uint32 pixelRight;
  Uint8 r;
  Uint8 g;
  Uint8 b;

  for(int i = 1; i + 1 < img -> w; i++)
  {
    for(int j = 1; j + 1< img -> h; j++)
    {
      pixelRLSA = getpixel(imgRLSA, i, j);
      SDL_GetRGB(pixel, imgRLSA -> format, &r, &g, &b);
      if (r == 0 && g == 0 && b == 0)    // si le pixel est noir, on regarde les pixels autour, si un d'eux est blanc alors
      {                                        // notre pixel est en bordure de bloc donc on le rend bleu
        pixelUp = getpixel(imgRLSA, i, j-1);
        SDL_GetRGB(pixelUp, imgRLSA -> format, &r, &g, &b);
        if (r == 255 && g == 255 && b == 255)    // pixel du haut
        {
          pixel = SDL_MapRGB(img -> format, 0, 0, 255);
          putpixel(img, i, j, pixel);
        }
        else
        {
          pixelDown = getpixel(imgRLSA, i, j+1);
          SDL_GetRGB(pixelDown, imgRLSA -> format, &r, &g, &b);
          if(r == 255 && g == 255 && b == 255)    // pixel d'en bas
          {
            pixel = SDL_MapRGB(img -> format, 0, 0, 255);
            putpixel(img, i, j, pixel);
          }
          else
          {
            pixelLeft = getpixel(imgRLSA, i-1, j);
            SDL_GetRGB(pixelLeft, imgRLSA -> format, &r, &g, &b);
            if(r == 255 && g == 255 && b == 255)    // pixel de gauche
            {
              pixel = SDL_MapRGB(img -> format, 0, 0, 255);
              putpixel(img, i, j, pixel);
            }
            else
            {
              pixelRight = getpixel(imgRLSA, i+1, j);
              SDL_GetRGB(pixelRight, imgRLSA -> format, &r, &g, &b);
              if(r == 255 && g == 255 && b == 255)    // pixel de droite
              {
                pixel = SDL_MapRGB(img -> format, 0, 0, 255);
                putpixel(img, i, j, pixel);
              }
            }
          }
        }
      }
    }
  }
}



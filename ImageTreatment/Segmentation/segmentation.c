#include "segmentation.h"


/*find if a line contain black pixel*/
int FindBlackPixel(SDL_Surface *img, int x)
{
  Uint32 pixel;
  int w;
  Uint8 r, g, b;
  int bool = 1; /*A boolean that memorize if the line contain black pixel or not*/
  w = img -> w;
  

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
    
  for(int i = x; i < end_line; i++)
 { 
    pixel = SDL_MapRGB(img->format, 1, 100, 100);
    putpixel(img, y, i, pixel);
    
 }
}

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
  return (white) / (black/2);    // renvoie la moyenne ( nombre de blanc / (nombre de noirs / 2)  )
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
  return(white) / (black );    //pareil qu'en horizontal
}

void blockDetection_horizontal(SDL_Surface *img)
{ 
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int hori = pixelSpacingHorizontal(img)*30;    // c'est une moyenne de l'espacement, pour avoir un seuil adapté a l'image et pas reunir deux blocs entre eux par erreur
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

// remplis les espaces verticaux entre deux pixels. fonctionne pareil que la version horizontale
void blockDetection_vertical(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int verti = pixelSpacingVertical(img) * 3;
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


// dessine les blocs en les noircissant entierement (fait un ET logique du RLSA horizontal et RLSA vertical)
// img c'est l'image qui va contenir des blocs remplis de noir
// imgHor a subi bloc detection horizontal
// imgver a subi bloc detection vertical
void drawBlocksMulti (SDL_Surface *img, SDL_Surface *imgHor, SDL_Surface *imgVer)
{
    Uint32 pixelHor;
    Uint32 pixelVer;
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    for(int i = 1; i + 1 < img -> w; i++)
    {
        for(int j = 1; j + 1< img -> h; j++)
        {
            pixelHor = getpixel(imgHor, i, j);
            SDL_GetRGB(pixelHor, imgHor -> format, &r, &g, &b);
            if (r == 0 && g == 0 && b == 0)
            {
                pixelVer = getpixel(imgVer, i, j);
                SDL_GetRGB(pixelVer, imgVer -> format, &r, &g, &b);
                if (r==0 && g==0 && b==0)
                {
                    pixel = SDL_MapRGB(img -> format, 0, 0, 0);
                     putpixel(img, i, j, pixel);
                }
            }
        }
    }
}


// drawBlocks mais que en mono colonne
void drawBlocks (SDL_Surface *img, SDL_Surface *imgHor)
{
  Uint32 pixelHor;
  Uint32 pixelLine;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int w;
  for(int i = 1; i + 1 < img -> w; i++)
  {
    for(int j = 1; j + 1< img -> h; j++)
    {
      pixelHor = getpixel(imgHor, i, j);
      SDL_GetRGB(pixelHor, imgHor -> format, &r, &g, &b);
      if (r== 0 && g == 0 && b == 0)
      {
         w = img -> w;
         for(int k = 0; k < w; k++)
         {
            pixelLine = SDL_MapRGB(img->format, 0, 0, 0);
            putpixel(img, k, j, pixelLine);
         }
      }
    }
  }
}

// Trace les lignes des blocs avec le RLSA
// img c'est l'image avec le texte et imgRLSA c'est l'image qui a subi blockDrawing
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
      SDL_GetRGB(pixelRLSA, imgRLSA -> format, &r, &g, &b);
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


int* histo(SDL_Surface *img)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int w;
  w = img -> w;
  int h;
  h = img -> h;
  int* histo = malloc(w * sizeof(int));

  for(int r = 0;r< w;r++ )
  {
      histo[r]=0;
  }

  for (int i = 0; i< w ; i ++) {
    int s = 0;
    for (int j = 0; j < h ; j++) {
      pixel = getpixel(img,i,j);
      SDL_GetRGB(pixel, img->format, &r, &g, &b);

      if ( r== 255) {
        s++; 
      }
    }
    histo[i]= h -s;
  }
  
  return histo;

}

void cutchar(SDL_Surface *img){
  int* histog=histo(img);
  for (int i = 0; i < img -> w; i++){
    if (histog[i]==0 || histog[i]==1){
      DrawAColumn(img, i, 0,img->h -1);
    }
  } 
  free(histog);
}

int seuil(SDL_Surface *img)
{
    int* histog=histo(img);
    int max = 0;
    int s =0;
    for(int i = 0;i < img -> w;i++){
        if (histog[i]==0){
            s++;
            //printf("S : %i \n",s);
        }
        else
        {
            if (s > max){
                max = s;
            }
            s =0;
        }
        
    }
    printf("MAX : %i \n",max);
    free(histog);
    return max;
}

int average(SDL_Surface *img)
{
    int* histog=histo(img);
    int s =0;
    int sum =0;
    int r = 0;
    int bool1 =1;
    for(int i = 0;i < img -> w;i++){
        if (histog[i]==0){
            if(bool1)
            {
                bool1 =0;
                r+=1;
            }
            s++;
        }
        else
        {
            sum+=s;
            bool1=1;
            s =0;
        }
        
    }
    free(histog);
    printf("AVERAGE : %i ", sum/r);
    return sum/r;
    
}

void cutword(SDL_Surface *img){

    printf("W %i H %i",img -> w, img ->h);
  int* histog=histo(img);
  int seuil1 = seuil(img);
  int bool1 = 1;
  int r = average(img);
  int s =0;
  int pos = 0;
  int i;
  
  printf("SEUIL : %i\n",seuil1);
 
  for (i = 0; i<img -> w; i++){
      //printf("%i \n",s);
   if (histog[i]==0){
       if(bool1){
           pos = i;
           bool1 = 0;
       }
        s++;
    }
    else{
        //printf("S : %i",s);
        if (s>= seuil1 - 1.5*r)
        {
            DrawAColumn(img, pos, 0,img->h);
        }
        bool1=1;
        s =0;
    }
  } 

  if (i == img -> w)
  {
      DrawAColumn(img, pos, 0,img->h);
  }
  free(histog);
}



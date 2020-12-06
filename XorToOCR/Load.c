# include "Load.h"

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
 int bpp = surf -> format -> BytesPerPixel;
 return (Uint8*)surf -> pixels + y * surf -> pitch + x * bpp;
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixelref(surface, x, y);
    switch(surface -> format -> BytesPerPixel) 
    {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
    }
    return 0;
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y *surface->pitch+x*nbOctetsParPixel;

    switch(nbOctetsParPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

SDL_Surface* resize(SDL_Surface *img, int x, int y)
{
    Uint32 pixel;
     SDL_Surface* new = SDL_CreateRGBSurface(0,
                              x,
                              y,
                              img -> format -> BitsPerPixel,0,0,0,0);
            int w = img -> w;
            int h = img -> h;
            float ratioX = (float) w / x;
            float ratioY = (float) h / y;
            for (int i = 0; i < x; ++i)
            {
                for (int j = 0; j < y; ++j)
                {
                    pixel = getpixel(img,(int) (i * ratioX), (int) (j * ratioY));
                    putpixel(new,i, j, pixel);
                }
            }
            return new;
}


SDL_Surface* CreateWhiteSurface(int x, int y, SDL_Surface* img)
{
    Uint32 pixel;
    SDL_Surface* new = SDL_CreateRGBSurface(0,
                              x,
                              y,
                              img -> format -> BitsPerPixel,0,0,0,0);
    
    for (int i = 0 ; i < new -> w; i++)
    {
        for (int j = 0; j < new -> h; j++)
        {
           pixel = SDL_MapRGB(img->format, 255, 255, 255);
           putpixel(new, i, j, pixel);
        }
    }

    return new;

}


int FindBlackPixelcol(SDL_Surface *img, int x)
{
  Uint32 pixel;
  int w;
  Uint8 r, g, b;
  int bool = 0; /*A boolean that memorize if the line contain black pixel or not*/
  w = img -> w;
  

  for(int i = 0; i < w; i++)
 {
    pixel = getpixel(img,i,x);
    SDL_GetRGB(pixel, img->format, &r, &g, &b);
        //printf("%d", r);
    if (r == 0)
    {
        bool = 1;
        break;
    }

 }
//printf("\n");
 return bool;
}

int FindBlackPixelrow(SDL_Surface *img, int x)
{
  Uint32 pixel;
  int h;
  Uint8 r, g, b;
  int bool = 0; /*A boolean that memorize if the line contain black pixel or not*/
  h = img -> h;
  

  for(int i = 0; i < h; i++)
 {
    pixel = getpixel(img,x,i);
    SDL_GetRGB(pixel, img->format, &r, &g, &b);

    if (r == 0)
    {
        bool = 1;
        break;
    }

 }
 return bool;
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

double *resizechar(SDL_Surface* img, int size)
{
    Uint32 pixel = 0;
    int startcol = 0;
    int endcol  = 0;
    int startrow = 0;
    int endrow  = 0;
    //SDL_Surface *loadedImage = 0;
    //loadedImage = SDL_LoadBMP("final12.bmp");

    binerize(img);

        for (int k = 0; k < img->w; k++)
    {
        for (int z = 0; z < img->h; z++)
        {
           printf("%d ", ((int) getpixel(img,z,k)));
        }
        printf("\n");
    }

    for (int i = 0; i < img->h; i++)
    {     
        if (FindBlackPixelrow(img,i))
        { 
            startcol = i;
            break;
        }
    }
    for (int i = img->h; i >= 0; i--)
    {
        if (FindBlackPixelrow(img,i))
        { 
            endcol = i+1;
            break;
        }
    }

        for (int i = 0; i < img->w; i++)
    {     
        if (FindBlackPixelcol(img,i))
        { 
            startrow = i;
            break;
        }
    }
    for (int i = img->w; i >= 0; i--)
    {     
        if (FindBlackPixelcol(img,i))
        { 
            endrow = i+1;
            break;
        }
    }

    SDL_Surface *new = NULL;
    int lencol = endcol - startcol;
    printf("%d, %d, %d\n", lencol, endcol, startcol);
    int lenrow = endrow - startrow;
    printf("%d, %d, %d\n", lenrow, endrow, startrow);
    if (lencol > lenrow){
        new = CreateWhiteSurface(lencol, lencol, img);
        int start = lencol/2 - lenrow/2;
        for (int k = startcol; k < endcol; k++)
        {
            for (int z = startrow; z < endrow; z++)
            {
                pixel = getpixel(img,z,k);
                putpixel(new,start+z,k-startcol,pixel);
            }
        }
    }
    else
    {
        new = CreateWhiteSurface(lenrow, lenrow, img);
        int start = lenrow/2 - lencol/2;
        for (int k = startcol; k < endcol; k++)
        {
            for (int z = startrow; z < endrow; z++)
            {
                pixel = getpixel(img,z,k);
                putpixel(new,z-startrow,k+start,pixel);
            }
        }
    }

printf("%d", size);
    //new = resize(new,size,size);
    double *image = (double*)malloc(lencol*lencol*sizeof(double));

    for (int k = 0; k < lencol; k++)
    {
        for (int z = 0; z < lencol; z++)
        {
            pixel = getpixel(new,k,z);
            image[k*lencol + z] = (double) pixel;
        }
    }

    /*for (int k = 0; k < lencol; k++)
    {
        for (int z = 0; z < lencol; z++)
        {
           printf("%d ", ((int) image[z*lencol + k]));
        }
        printf("\n");
    }*/

    return image;
}



/*int main(void){

    SDL_Surface *loadedImage = 0;
    loadedImage = SDL_LoadBMP("image.bmp");
    Uint32 pixel = 0;

    if (!loadedImage)
    {
        printf("Can't find the bmp file\n");
        return 1;
    }

    loadedImage = resizechar(loadedImage);

    for (int k = 0; k < 32; k++)
    {
        for (int z = 1; z < loadedImage->w; z++)
        {
        pixel = getpixel(loadedImage,z,k);
           printf("%d ",pixel);
        }
        printf("\n");
    }

    SDL_FreeSurface(loadedImage);


    return 0;
}*/
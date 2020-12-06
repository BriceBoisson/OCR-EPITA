# include "tools.h"

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





void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

void array_swap(int array[], size_t i, size_t j)
{
  int element1 = array[i];
  int element2 = array[j];
  array[i] = element2;
  array[j] = element1;
}
void array_select_sort(int array[], size_t len)
{
  size_t i = 0;
  size_t j;
  int min_index;
  while(i<len)
  {
    /* Find Min Index */
    j= i;
    min_index = j;
    while(j<len)
    {
        if(array[j]<array[min_index])
        {
            min_index = j;
        }
        j+=1;
    }
    array_swap(array,i,min_index);
    i++;
  }
}

SDL_Surface* copy_image(SDL_Surface *img)
{
  Uint32 pixel;
  SDL_Surface* copy;
  copy = SDL_CreateRGBSurface(0,
                              img -> w,
                              img -> h,
                              img -> format -> BitsPerPixel,0,0,0,0);
  for(int i = 0; i < img -> w; i++)
  {
    for(int j = 0;j < img -> h; j++)
    {
      pixel = getpixel(img, i, j);
      putpixel(copy, i, j, pixel);
    }
  }
  return(copy);
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


int FindBlackPixelv2(SDL_Surface *img, int x)
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

    if (r == 0)
    {
        bool = 1;
        break;
    }

 }

 return bool;
}

SDL_Surface * resizechar(SDL_Surface* img)
{
    Uint32 pixel = 0;
    int start = 0;
    int end  = 0;
    int booleen = 0;
    SDL_Surface *loadedImage = 0;
    //loadedImage = SDL_LoadBMP("final12.bmp");


    for (int i = 0; i < img->h; i++)
    {     

        if (FindBlackPixelv2(img,i))
        {
            
            if (!booleen)
            {
                booleen = 1;
                start = i;
            }
        }
        else
        {
            if(booleen)
            {
                end = i;
                booleen = 0;
            }
        }
    } 

    printf("end : %i, begin : %i \n",end,start);

    SDL_Surface *new = CreateWhiteSurface(img->w+20, end-start,img);

    for (int k = start; k < end; k++)
    {
        for (int z = 1; z < img->w; z++)
        {
            pixel = getpixel(img,z,k);
            putpixel(new,z+10,k-start,pixel);
        }
    }


    return resize(new,32,32);

}



int main(void){

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
}
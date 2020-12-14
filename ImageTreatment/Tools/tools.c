# include "tools.h"

# include <math.h>

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
    Uint8 *p = pixelref(surface, x, y);

    switch(surface -> format -> BytesPerPixel)
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


void pause1()
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
                    pixel = getpixel(img,(int) (i * ratioX), 
                                        (int) (j * ratioY));
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

    return (new);

}




SDL_Surface* rotate(double teta, SDL_Surface* img)
{
    double radian = (teta * M_PI) / 180.0;
    int certerx = round(((img->w+1)/2)-1);
    int centery = round(((img->h+1)/2)-1);
    int xprime = 0;
    int yprime = 0;
    int h = img->h;
    int w = img->w;
    Uint32 pixel = 0;
    

    /*if (teta == 90)
    {
        int stock = w;
        w = h;
        h= stock;
    }*/
    SDL_Surface * new = CreateWhiteSurface(w,h,img);

    for (int i = 0; i < img -> w; i++)
    {
        for(int j = 0; j < img -> h ; j++)
        {
            xprime = round((double)(i-certerx)*cos(radian)+
                            (double)(j-centery)*sin(radian));
            yprime = round((double)(j-centery)*cos(radian) -  
                            (double)(i-certerx)*sin(radian));
                            
            xprime += certerx;
            yprime += centery;

            if (xprime >= 0 && xprime < img->w && yprime < img->h && 
                yprime >= 0)
            {
                pixel = getpixel(img,i,j);
                putpixel(new,xprime,yprime,pixel);
            }
        }        
    }
    return new; 
}

double houghtrasformy(SDL_Surface *img)
{
    double maxrow = sqrt((img->w*img->w)+(img->h*img->h));
    int maxteta = 180;
    Uint8 r,g,b;
    int *tab = calloc((size_t)(maxrow*181),sizeof(int));
    Uint32 pixel = 0;

    for (int i = 0; i < img->w; i++)
    {
        for(int j = 0; j < img->h;  j++)
        {
            pixel = getpixel(img,i,j);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);

            if (r == 0 && g == 0 && b == 0)
            {
                int x = i - (img->w / 2);
                int y = j - (img->h / 2);

                for(int  teta_i = 0; teta_i < maxteta; teta_i++)
                {
                    double teta = ((double)teta_i /180.0)*M_PI;
                    double row = x * cos(teta) + y * sin(teta);
                    size_t i_rho = 0.5 + (row / maxrow + 0.5) * (maxrow+1);
                    tab[teta_i+maxteta*i_rho]+=1;
                }
            }
            
        }
    }

    double resulte = maxhough(tab,maxrow);
    return resulte;    
}

double maxhough(int *tab, size_t maxrow)
{
    
    double ThetaR;
    int max = 0;
    size_t maxteta = 180;
    for (size_t i = 0; i < maxrow; ++i) {
        for (size_t j = 0; j < maxteta; ++j) {
            if (tab[j + i * maxteta] > max) {
                max = tab[j + i * maxteta];
                ThetaR = j;
            }
        }
    }
    return ThetaR;
}


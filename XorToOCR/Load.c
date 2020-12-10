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

double* resize(double *img, int w, int h, int x, int y)
{
    double *image = (double*)calloc(x*y, sizeof(double));
    float ratioX = (float) w / x;
    float ratioY = (float) h / y;
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            image[i*x + j] = img[((int) (i * ratioY))*w + ((int) (j * ratioX))];
            //pixel = getpixel(img,(int) (i * ratioX), (int) (j * ratioY));
            //putpixel(new,i, j, pixel);
        }
    }
    return image;
}


int FindBlackPixelrow(double *img, int w, int x)
{

    int bool = 0; /*A boolean that memorize if the line contain black pixel or not*/
    double pixel;
       //printf("\n%d: ", x);

  for(int i = 0; i < w; i++)
 {
    pixel = img[x*w + i];
//printf("%d ", (int) pixel);
    if (pixel == 1)
    {
        bool = 1;
        break;
    }

 }
 return bool;
}

int FindBlackPixelcol(double *img, int w, int h, int x)
{
    int bool = 0; /*A boolean that memorize if the line contain black pixel or not*/
    double pixel;

    //printf("\n%d : ", x);

  for(int i = 0; i < h; i++)
 {
    pixel = img[i*w + x];
    //printf("%f ", pixel);
    if (pixel == 1)
    {
        bool = 1;
        break;
    }

 }
 return bool;
}

void get_binerize_matrix(SDL_Surface *img, double *image)
{
  /* Variables */
  Uint32 pixel;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  int w = img -> w;
  int h = img -> h;
  
 for(int i = 0; i < h; i++)
 {
   for(int j = 0; j < w; j++)
   {
     pixel = getpixel(img,j,i);
     SDL_GetRGB(pixel, img->format, &r, &g, &b);

     Uint32 average = (r+b+g) /3;

     if(average > 150) /*we can make an average here*/
     {
         image[i*w + j] = 0.0;
     }
     else
     {
        image[i*w + j] = 1.0;
     }
   }
 }

}

double *resizechar(SDL_Surface* img, int size)
{
    int startcol = 0;
    int endcol  = 0;
    int startrow = 0;
    int endrow  = 0;

    int img_w = img->w;
    int img_h = img->h;

    double *img_array = (double*)malloc(img_h*img_w*sizeof(double));

    get_binerize_matrix(img, img_array);

    for (int i = 0; i < img_w; i++)
    {     
        if (FindBlackPixelcol(img_array, img_w, img_h, i))
        { 
            startcol = i;
            break;
        }
    }
    for (int i = img_w-1; i >= 0; i--)
    {
        if (FindBlackPixelcol(img_array, img_w, img_h, i))
        { 
            endcol = i+1;
            break;
        }
    }
    for (int i = 0; i < img_h; i++)
    {     
        if (FindBlackPixelrow(img_array, img_w, i))
        { 
            startrow = i;
            break;
        }
    }
    for (int i = img_h-1; i >= 0; i--)
    {     
        if (FindBlackPixelrow(img_array, img_w, i))
        { 
            endrow = i+1;
            break;
        }
    }

    double *img_carre;
    int img_carre_size;
    int lencol = endcol - startcol;
    int lenrow = endrow - startrow;
    if (lencol > lenrow){
        img_carre_size = lencol;
        img_carre = (double*)calloc(lencol*lencol, sizeof(double));
        int start = lencol/2 - lenrow/2;
        for (int k = startrow; k < endrow; k++)
        {
            for (int z = startcol; z < endcol; z++)
            {
                img_carre[(k-startrow+start)*lencol+z-startcol] = img_array[k*img_w + z];
            }
        }
    }
    else
    {
        img_carre_size = lenrow;
        img_carre = (double*)calloc(lenrow*lenrow, sizeof(double));
        int start = lenrow/2 - lencol/2;
        for (int k = startrow; k < endrow; k++)
        {
            for (int z = startcol; z < endcol; z++)
            {
                img_carre[(k-startrow)*lenrow+z-startcol+start] = img_array[k*img_w + z];
            }
        }
    }

    double *image;
    image = resize(img_carre, img_carre_size, img_carre_size, size, size);

    SDL_FreeSurface(img);
    free(img_array);
    free(img_carre);

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
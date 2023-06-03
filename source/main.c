/*
SDL Chaste Image

This program is an image viewer that makes use of "SDL_image" to load and save PNG files.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

char filename[256];
int scale=1;
SDL_Window *window = NULL;
SDL_Surface *surface,*bitmap,*bitmap_temp;
int loop=1;
SDL_Event e;

int main(int argc, char **argv)
{
 int x;

/*process command line arguments*/

 x=0;
 while(x<argc)
 {
  /*printf("argv[%i]=%s\n",x,argv[x]);*/
  x++;
 }

 /*if a command line argument is provided, open that file*/
 if(argc>1)
 {
  printf("argc=%i\n",argc);
  strcpy(filename,argv[1]);
 }
 else
 {
  printf("Enter a bitmap file as an argument to load it.\n");
  return 0;
 }

 /*test by using hard coded bitmap file*/
 /*strcpy(filename,"./bitmap/Chastity_Progress_Flag.png");*/

 printf("opening filename: %s\n",filename);

 /*IMG_Init(IMG_INIT_PNG);*/

 bitmap_temp=IMG_Load(filename);

 if(bitmap_temp==NULL)
 {
  printf( "SDL could not load temporary image! SDL_Error: %s\n",SDL_GetError());
  return 0;
 }


 bitmap=SDL_ConvertSurfaceFormat(bitmap_temp,SDL_PIXELFORMAT_BGRA32,0);


 if(bitmap==NULL)
 {
  printf( "SDL could not load main image! SDL_Error: %s\n",SDL_GetError());
  return 0;
 }

 SDL_FreeSurface(bitmap_temp);


 printf("bitmap loaded:\n");
 printf("bitmap width: %d\n",bitmap->w);
 printf("bitmap height: %d\n",bitmap->h);


 /*bitmap_clear_alpha(bitmap);*/
 /*return 0;*/

 window=SDL_CreateWindow(filename,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,bitmap->w*scale,bitmap->h*scale,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 surface = SDL_GetWindowSurface( window ); /*get surface for this window*/

 SDL_BlitSurface(bitmap,NULL,surface,NULL);
/*bitmap_copy_to_surface_scaled(bitmap,surface);*/

 SDL_UpdateWindowSurface(window);

 loop=1;
 while(loop)
 {
  /*test for events and only process if they exist*/
  while(SDL_PollEvent(&e))
  {
   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }
  }
 }

 if(0){IMG_SavePNG(surface,"output.png");}

 /*free memory of bitmap now that we are done with it*/
 SDL_FreeSurface(bitmap);
 SDL_DestroyWindow(window);
 SDL_Quit();

 return 0;
}


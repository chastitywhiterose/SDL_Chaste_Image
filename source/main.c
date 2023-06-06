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

int width,height;

char filename[256],text[256];
SDL_Window *window = NULL;
SDL_Surface *surface,*bitmap,*bitmap_temp;
int loop=1;
SDL_Event e;

#include "sdl_chastefont_surface.h"

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
 SDL_FreeSurface(bitmap_temp);

 }
 else
 {
  printf("No bitmap was given as argument. Attempting to create blank image.\n");
  bitmap=SDL_CreateRGBSurfaceWithFormat(0,1280,720,32,SDL_PIXELFORMAT_BGRA32);
  SDL_FillRect(bitmap,NULL,0xFF000000);
  strcpy(filename,"Help Page");

  printf("Enter file as command line to display it.\nExample:\n\n%s ./bitmap/Chastity_Progress_Flag.png\n\n",argv[0]);
 }

 if(bitmap==NULL)
 {
  printf( "SDL could not load main image! SDL_Error: %s\n",SDL_GetError());
  return 0;
 }

 width=bitmap->w;
 height=bitmap->h;

 printf("bitmap loaded:\n");
 printf("bitmap width: %d\n",width);
 printf("bitmap height: %d\n",height);


 window=SDL_CreateWindow(filename,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 surface = SDL_GetWindowSurface( window ); /*get surface for this window*/

 font_8=chaste_font_load("./font/FreeBASIC Font 8.bmp");
 main_font=font_8;



 SDL_BlitSurface(bitmap,NULL,surface,NULL);

 
if(argc==1)
{
 chaste_font_draw_string("SDL Chaste Image written by Chastity White Rose",10,10);

 chaste_font_draw_string_scaled("Progress Flag sample image designed by Chastity\nafter looking at similar images",64,500,2);


 sprintf(text,"Enter file as command line to display it.\nExample:\n\n%s ./bitmap/Chastity_Progress_Flag.png",argv[0]);

 chaste_font_draw_string_scaled_color(text,64,300,3,0xFFFFFF);
}

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

 /*free memory of bitmaps now that we are done with them*/
 SDL_FreeSurface(font_8.surface);
 SDL_FreeSurface(bitmap);
 SDL_DestroyWindow(window);
 SDL_Quit();

 return 0;
}


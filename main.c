#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "defs.h"
#include "globais.h"
#include "funcoes.h"
#include <stdlib.h>

int main( int argc, char* args[] ) {
    SDL_Rect srcRect, dstRect, dstRect2;
    int quit;
    /*Event handler*/
    SDL_Event e;

    /*Start up SDL and create window*/
    if( !init() ) {
        printf( "Failed to initialize!\n" );
    }
    else {
        /*Load media*/
        if( !loadMedia() ) {
            printf( "Failed to load media!\n" );
        }
        else {
            /*Create NPC*/
            ball = createNPC(SCREEN_WIDTH/2 - IMAGE_WIDTH/2, SCREEN_HEIGHT/2 - IMAGE_HEIGHT/2, rand() % 2 ? -1: 1, rand() % 2 ? -1: 1, gJPGSurface);
			barra = createBAR(300, 450, 0, gJPGBar);
			matrizBlocos();
            /*Main loop flag*/
            quit = false;




            /*While application is running*/
            while( !quit ) {
                while( SDL_PollEvent( &e ) != 0 ) {
                    switch(e.type){
						case SDL_QUIT:
								quit = true;
								break;
						break;
					}
					if(e.type == SDL_KEYDOWN){
						switch(e.key.keysym.sym){
							case SDLK_ESCAPE:
								quit = true;
								break;
							case SDLK_LEFT:
								barra.stepX = -2;
								break;
							case SDLK_RIGHT:
								barra.stepX = 2;
								break;
							break;
						}
					}

					if(e.type == SDL_KEYUP){
						switch(e.key.keysym.sym){
							case SDLK_LEFT:
								barra.stepX = 0;
								break;
							case SDLK_RIGHT:
								barra.stepX = 0;
								break;
						}
					}
                }	

                /*Fill the surface white*/
                SDL_FillRect( gScreenSurface, NULL,
                              SDL_MapRGB( gScreenSurface->format,
                              20, 20, 20 ) );
		
                moveNPC(&ball);
				attBlocos();
				attBarra();

                srcRect.x = 0; srcRect.y = 0;
                srcRect.w = IMAGE_WIDTH;
                srcRect.h = IMAGE_HEIGHT;
                dstRect.x = ball.posX;
                dstRect.y = ball.posY;
		
				//dstRect2.x = barra.posX;
                //dstRect2.y = barra.posY;

                if( SDL_BlitSurface( ball.image, &srcRect,
                                     gScreenSurface, &dstRect ) < 0 ) {
                    printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
                    quit = true;
                }
				
				srcRect.x = 0; srcRect.y = 0;
				srcRect.w = 64;
				srcRect.h = 20;
				dstRect.x = barra.posX;
				dstRect.y = barra.posY;
				
				if( SDL_BlitSurface( barra.image, NULL,
                                     gScreenSurface, &dstRect) < 0 ) {
                    printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
                    quit = true;
                }

                /*Update the surface*/
                SDL_UpdateWindowSurface( gWindow );

                /* Not so good solution, depends on your computer*/
                SDL_Delay(5);
            }
        }
    }

    /*Free resources and closing SDL*/
    closing();

    return 0;
}


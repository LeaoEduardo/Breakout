#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"
#include "globais.h"

int loadSound(){
  
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
  Mix_AllocateChannels(16);

  background = Mix_LoadMUS("JacoPastorius-TheChicken.mp3");
  if (!background){
	  printf("mp3: SDL error=%s\n", SDL_GetError());
	  return false;
  }
  
  hitBrick = Mix_LoadWAV("beepst.wav");
  if (!hitBrick){
	  printf("WAV: SDL error=%s\n", SDL_GetError());
	  return false;
  }
    
  hitWall = Mix_LoadWAV("beep.wav");
  if (!hitWall){
	  printf("WAV: SDL error=%s\n", SDL_GetError());
	  return false;
  }
    
  hitBar = Mix_LoadWAV("bop.wav");
  if (!hitBar){
	  printf("WAV: SDL error=%s\n", SDL_GetError());
	  return false;
  } 
	
  hitTop = Mix_LoadWAV("bop2.wav");
  if (!hitTop){
	  printf("WAV: SDL error=%s\n", SDL_GetError());
	  return false;
  } 
    
  hitBottom = Mix_LoadWAV("datisyufail.wav");
  if (!hitBottom){
	  printf("WAV: SDL error=%s\n", SDL_GetError());
	  return false;
  } 
    
  levelUp = Mix_LoadWAV("youwin.wav");
  if (!levelUp){
	  printf("WAV: SDL error=%s\n", SDL_GetError());
	  return false;
  } 
    
  gameOver = Mix_LoadWAV("GameOver.wav");
  if (!gameOver){
	  printf("WAV: SDL error=%s\n", SDL_GetError());
	  return false;
  }
   
  Mix_PlayMusic(background, -1);
  Mix_VolumeMusic(30);

  return true;
}

  void moveNPC(NPC *p) {
    p->posX += p->stepX;
    p->posY += p->stepY;
    int i, j;

    if ( (p->posX + IMAGE_WIDTH > SCREEN_WIDTH) ||
         (p->posX < 0) ) {
        p->stepX = -p->stepX;
        p->posX += p->stepX;
        Mix_PlayChannel(-1,hitWall,0);
    }
    
    if (p->posY + IMAGE_HEIGHT > SCREEN_HEIGHT) {
        p->stepY = -p->stepY;
        p->posY += p->stepY;
        Mix_PlayChannel(-1,hitBottom,0);
    }
    
    
    if (p->posY < 0) {
        p->stepY = -p->stepY;
        p->posY += p->stepY;
        Mix_PlayChannel(-1,hitTop,0);
    }
    
    for (i=0; i<8; i++){
		if(i%2 == 0){
			for (j=0; j<10; j++){
				if(blocos[i][j].life > 0){
					if( (p->posY == blocos[i][j].posY + 20 )&& ((p->posX >= blocos[i][j].posX) && (p->posX <= blocos[i][j].posX +64))){
								p->stepY = -p->stepY;
								p->posY += p->stepY;
								blocos[i][j].life -= 1;
					}
					if( (p->posY + 18 == blocos[i][j].posY )&& ((p->posX + 18 >= blocos[i][j].posX) && (p->posX <= blocos[i][j].posX +64))){
								p->stepY = -p->stepY;
								p->posY += p->stepY;
								blocos[i][j].life -= 1;
					}
					if( (p->posX == blocos[i][j].posX + 64 )&& ((p->posY >= blocos[i][j].posY) && (p->posY <= blocos[i][j].posY + 18))){
								p->stepY = -p->stepY;
								p->posY += p->stepY;
								blocos[i][j].life -= 1;
					}
					if( (p->posX + 18 == blocos[i][j].posX  )&& ((p->posY + 18 >= blocos[i][j].posY) && (p->posY <= blocos[i][j].posY + 18))){
								p->stepY = -p->stepY;
								p->posY += p->stepY;
								blocos[i][j].life -= 1;
					}
				
				}
			}
		}
		else{
			for (j=0; j<9; j++){
				if(blocos[i][j].life > 0){
					if( (p->posY == blocos[i][j].posY + 20 )&& ((p->posX >= blocos[i][j].posX) && (p->posX <= blocos[i][j].posX +64))){
								p->stepY = -p->stepY;
								p->posY += p->stepY;
								blocos[i][j].life -= 1;
					}
					if( (p->posY + 18 == blocos[i][j].posY )&& ((p->posX + 18  >= blocos[i][j].posX) && (p->posX <= blocos[i][j].posX +64))){
								p->stepY = -p->stepY;
								p->posY += p->stepY;
								blocos[i][j].life -= 1;
					}
					if( (p->posX == blocos[i][j].posX + 64 )&& ((p->posY >= blocos[i][j].posY) && (p->posY <= blocos[i][j].posY + 18))){
								p->stepX = -p->stepX;
								p->posX += p->stepX;
								blocos[i][j].life -= 1;
					}
					if( (p->posX + 18 == blocos[i][j].posX  )&& ((p->posY +18 >= blocos[i][j].posY) && (p->posY <= blocos[i][j].posY + 18))){
								p->stepX = -p->stepX;
								p->posX += p->stepX;
								blocos[i][j].life -= 1;
					}
				}
			}
		}
	}
    
    
    
}

/*Create NPC*/
NPC createNPC( int posX, int posY, int stepX, int stepY,
               SDL_Surface *image) {
    NPC p;

    p.posX = posX;
    p.posY = posY;
    p.stepX = stepX;
    p.stepY = stepY;
    p.image = image;
    return p;
}

SDL_Surface* loadSurface( char *path ) {
    /*The final optimized image*/
    SDL_Surface* optimizedSurface = NULL;

    /*Load image at specified path*/
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    }
    else {
        /*Convert surface to screen format*/
        optimizedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
        if( optimizedSurface == NULL ) {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        /*Get rid of old loaded surface*/
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

BLOCO createBAR(int posX, int posY, int stepX, SDL_Surface *image){
    BLOCO p;

    p.posX = posX;
    p.posY = posY;
    p.stepX = stepX;
    p.image = image;

  return p;

}

BLOCO createBLOCO ( int posX, int posY, 
               SDL_Surface *image) {
    BLOCO p;

	 
    p.posX = posX;
    p.posY = posY;
    p.life = rand() % 3 + 1;
    p.image = image;


    return p;

}

void attBlocos(){
	SDL_Rect dstRect;
	int i, j;
	
    for (i=0; i<8; i++){
		if(i%2 == 0){
			for (j=0; j<10; j++){
	
				dstRect.x = blocos[i][j].posX;
				dstRect.y = blocos[i][j].posY;
				if(blocos[i][j].life > 0){
					if( SDL_BlitSurface( blocos[i][j].image, NULL, gScreenSurface, &dstRect ) < 0 ) {
						printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
					}
				}			
			}
		}
		else{
			for (j=0; j<9; j++){
	
				dstRect.x = blocos[i][j].posX;
				dstRect.y = blocos[i][j].posY;
				if(blocos[i][j].life > 0){
					if( SDL_BlitSurface( blocos[i][j].image, NULL, gScreenSurface, &dstRect ) < 0 ) {
						printf( "SDL could not blit! SDL Error: %s\n", SDL_GetError() );
					}
				}			
			}
		}
	}

}

void attBarra(){
	
	barra.posX += barra.stepX;
	if(barra.posX < 0 || barra.posX + 64 > SCREEN_WIDTH){
		barra.posX -= barra.stepX;
	}
	
}

void matrizBlocos(){
	
	int i, j;
	int posX, posY;
	int success = true;
	
	blocos = (BLOCO **) calloc(8, sizeof(BLOCO *));
    if (!blocos) {
        puts("Erro ao alocar memoria");
        success = false;
    }
    for (i = 0; i < 8; i++) {
		if(i%2 == 0){
			blocos[i] = (BLOCO *) calloc(10, sizeof(BLOCO));
		}
		else{
			blocos[i] = (BLOCO *) calloc(9, sizeof(BLOCO));
		}
        if (!blocos[i]) {
            puts("Erro ao alocar memoria");
			success = false;
        }
    }
    
    for (i=0, posY=0; i<8; i++){
		if(i%2 == 0){
			for (j=0, posX = 0; j<10; j++){
				blocos[i][j] =	createBLOCO ( posX, posY, gJPGBlocos);
				posX += 64;
			}
		}
		
		
		else{
			for (j=0, posX = 32; j<9; j++){
				blocos[i][j] =	createBLOCO ( posX, posY, gJPGBlocos);
				posX += 64;
			}
		}
		posY += 20;
	}
	
	
}
int loadMedia() {
    /*Loading success flag*/
    int success = true;
    /*uint32_t colorKey;*/

    /*Load PNG surface*/
    gPNGBack = loadSurface ("./breakout_bg.png");
    gJPGSurface = loadSurface( "./circle.jpeg" );
    gJPGBlocos = loadSurface( "./bloco.jpeg" );
    gJPGBar = loadSurface("./barra.jpeg");
    if( gJPGSurface == NULL || gJPGBlocos == NULL || gJPGBar == NULL) {
        printf( "Failed to load image! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    
    return success;
}

int init() {
    /*Initialization flag*/
    int success = true;

    srand(time(NULL));

    /*Initialize SDL*/
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        /*Create window*/
        gWindow = SDL_CreateWindow( "Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            /*Initialize JPG and PNG loading */
            int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            else {
                /*Get window surface*/
                gScreenSurface = SDL_GetWindowSurface( gWindow );
		if (TTF_Init()<0){
                  printf("TTF could not initialize! TTF ERROR: %s\n", TTF_GetError());
                  success = false;
            }
		}
	loadSound();
    }
	}
	return success;

}

void closing() {
    /*Free loaded image*/
    SDL_FreeSurface( gJPGSurface );
    gJPGSurface = NULL;

    /*Destroy window*/
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    Mix_FreeMusic(background);
    Mix_FreeChunk(hitBrick);
    Mix_FreeChunk(hitWall);
    Mix_FreeChunk(hitBar);
    Mix_FreeChunk(hitBottom);
    Mix_FreeChunk(hitTop);
    Mix_FreeChunk(levelUp);
    Mix_FreeChunk(gameOver);

    /*Quit SDL subsystems*/
    IMG_Quit();
    SDL_Quit();
} 


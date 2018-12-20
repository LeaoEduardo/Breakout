#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "defs.h"
#include "globais.h"

SDL_Window* gWindow = NULL;
NPC ball;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gJPGSurface = NULL;
Mix_Music* background;
Mix_Chunk* hitBrick;
Mix_Chunk* hitWall;
Mix_Chunk* hitBar;
Mix_Chunk* hitBottom;
Mix_Chunk* hitTop;
Mix_Chunk* levelUp;
Mix_Chunk* gameOver;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int false = 0;
const int true = 1;
const int IMAGE_WIDTH = 18;
const int IMAGE_HEIGHT = 18;
SDL_Surface* gJPGBlocos1 = NULL;
SDL_Surface* gJPGBlocos2 = NULL;
SDL_Surface* gJPGBlocos3 = NULL;
SDL_Surface* gPNGBack = NULL;
BLOCO **blocos;
BARRA barra;
PLAYER player;
GAMESTATS game;
SDL_Surface* gJPGBar = NULL;
SDL_Surface* gJPGGameOver = NULL;
SDL_Surface* gPNGOp = NULL;
SDL_Surface* gPNGBackOp;
SDL_Surface* gPNGVolumeMais;
SDL_Surface* gPNGVolumeMenos;
SDL_Surface* gPNGMenu;
SDL_Surface* gPNGOpOn = NULL;
SDL_Surface* gPNGRank = NULL;
SDL_Surface* gPNGRankOn = NULL;
SDL_Surface* gPNGInit = NULL;
SDL_Surface* gPNGInitOn = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;
SDL_Surface* gPNGFundo = NULL;
char play;
int volume = 64;

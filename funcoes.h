#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "globais.h"
#include "defs.h"

int init();
int loadMedia();
int loadSound();
void closing();
void fimdefase();
void createPlayer();
void criarLVL();
SDL_Surface* loadSurface( char *path );
NPC createNPC( int posX, int posY, int stepX, int stepY, SDL_Surface *image);
int moveNPC(NPC *p, int quit);
void attBarra();
void matrizBlocos();
BLOCO createBLOCO ( int posX, int posY);
void attBlocos();
BARRA createBAR ( int posX, int posY, int stepX, SDL_Surface *image);
void printPlayerStats(PLAYER player, TTF_Font* fonteScore, GAMESTATS game);
TTF_Font* loadFont(char* arquivoFonte, int size);
SDL_Surface* createSurfaceTTF(char* texto,TTF_Font* fonte,int colorR,int colorG,int colorB);
int blitMenu(char play, int quit);
int blitGameOver(int quit);
int blitLevel(int quit, TTF_Font *score);
char definePlay(char play, SDL_Event e);
int moveBar(int quit, SDL_Event e);
int blitOpcoes(int quit, SDL_Event e);

#endif

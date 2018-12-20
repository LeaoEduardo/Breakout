#ifndef DEFS_H
#define DEFS_H

typedef struct _NPC {
    int posX;
    int posY;
    int stepX;
    int stepY;
    SDL_Surface* image;
    int imgW;
    int imgH;
} NPC;

typedef struct _BLOCOS {
	int posX;
	int posY;
	int life;
} BLOCO;

typedef struct _BARRA {
    int posX;
    int posY;
    int stepX;
    SDL_Surface* image;
    int imgW;
    int imgH;
} BARRA;

typedef struct _PLAYER {
    char playerName[8];
    int lives;
    int level;
    int score;
} PLAYER;

typedef struct _GAMESTATS{
  int level;
	int total_level_score;
} GAMESTATS;

#endif

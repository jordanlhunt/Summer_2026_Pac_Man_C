#ifndef MAIN_H
#define MAIN_H
#include "../include/gamecontext.h"
#include "../include/leveldata.h"
#include "../include/map.h"
#include "../include/player.h"
#include "common.h"
void initializeSDL();
void loadAssets();
void initializeGameState();
void handleInput();
void drawGame();
void updateGame();
void delayFramerate(Uint32 startTime);
void cleanup(SDL_Renderer *, SDL_Window *);
#endif
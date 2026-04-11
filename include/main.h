#ifndef MAIN_H
#define MAIN_H
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
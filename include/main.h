#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL_stdinc.h>

void initializeSDL();
void loadAssets();
void initalizeGameState();
void handleInput();
void drawGame();
void updateGame();
void delayFramerate(Uint32 startTime);

#endif
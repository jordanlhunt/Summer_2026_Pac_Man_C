#ifndef MAIN_H
#define MAIN_H
#include "../include/ecs/ecs.h"
#include "../include/gamecontext.h"
#include "../include/leveldata.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/systems/collisionSystem.h"
#include "../include/systems/inputSystem.h"
#include "../include/systems/movementSystem.h"
#include "../include/systems/renderSystem.h"
#include "../include/gameinitialization.h"
#include "common.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
void initializeSDL();
void loadAssets();
void initializeGameState();
void handleInput();
void drawGame();
void updateGame();
void delayFramerate(Uint32 startTime);
void cleanup(SDL_Renderer *, SDL_Window *);
#endif

#ifndef MAIN_H
#define MAIN_H
#include "../include/audio.h"
#include "../include/ecs/ecs.h"
#include "../include/gamecontext.h"
#include "../include/gameinitialization.h"
#include "../include/leveldata.h"
#include "../include/map.h"
#include "../include/systems/collisionSystem.h"
#include "../include/systems/inputSystem.h"
#include "../include/systems/movementSystem.h"
#include "../include/systems/renderSystem.h"
#include "common.h"
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#define MAX_DELTA_TIME 0.05f
void initializeSDL();
void loadAssets();
void initializeGameState();
void handleInput();
void drawGame();
void updateGame();
void DelayFramerate(Uint32 startTime);
void updateFrightenedModeTimer(GameContext *gameContext, float deltaTime);
void cleanup(SDL_Renderer *, SDL_Window *);
#endif

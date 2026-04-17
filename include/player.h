#ifndef PLAYER_H
#define PLAYER_H
// Includes
#include "common.h"
#include "entity.h"
#include "gamecontext.h"
// Forward Delectations
typedef struct GameContext GameContext;
typedef struct SDL_Renderer SDL_Renderer;
void initializePlayer(GameContext *gameContext);
void updatePlayer(GameContext *gameContext);
void drawPlayer(GameContext *gameContext, SDL_Renderer *renderer);
#endif
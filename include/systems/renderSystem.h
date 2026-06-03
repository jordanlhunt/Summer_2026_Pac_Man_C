#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H
#include "../../include/ecs/ecs.h"
#include "../../include/gamecontext.h"
typedef enum RenderLayer {
  RENDERLAYER_BACKGROUND,
  RENDERLAYER_EDIBLE,
  RENDERLAYER_GHOST,
  RENDERLAYER_PLAYER
} RenderLayer;
void RenderSystem(GameContext *gameContext, SDL_Renderer *renderer);
#endif

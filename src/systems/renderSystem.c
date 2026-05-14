#include "../../include/systems/renderSystem.h"
#include <SDL2/SDL_render.h>

void RenderSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  if (ECS_HasComponent(gameContext->playerEntity,
                       COMPONENT_POSITION | COMPONENT_RENDERABLE) == false) {
    return;
  }
  Position *position = ECS_GetPosition(gameContext->playerEntity);
  Renderable *renderData = ECS_GetRenderable(gameContext->playerEntity);
  SDL_Rect renderRect = {position->column * MAP_GRID_CELL_SIZE,
                         position->row * MAP_GRID_CELL_SIZE, renderData->width,
                         renderData->height};
  SDL_SetRenderDrawColor(renderer, renderData->red, renderData->green,
                         renderData->blue, renderData->alpha);
  SDL_RenderFillRect(renderer, &renderRect);
}
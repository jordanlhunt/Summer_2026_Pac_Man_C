#include "../../include/systems/renderSystem.h"
#include <SDL2/SDL_render.h>

void RenderSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  int activeEntitiesCount = ECS_GetActiveEntitiesCount();

  for (int i = 0; i < activeEntitiesCount; i++) {
    Entity activeEntity = ECS_GetActiveEntity(i);
    if (ECS_HasComponents(activeEntity,
                          COMPONENT_POSITION | COMPONENT_RENDERABLE) == false) {
      continue;
    }
    Position *position = ECS_GetPosition(activeEntity);
    Renderable *renderData = ECS_GetRenderable(activeEntity);
    SDL_Rect renderRect = {position->column * MAP_GRID_CELL_SIZE,
                           position->row * MAP_GRID_CELL_SIZE,
                           renderData->width, renderData->height};
    SDL_SetRenderDrawColor(renderer, renderData->red, renderData->green,
                           renderData->blue, renderData->alpha);
    SDL_RenderFillRect(renderer, &renderRect);
  }
}
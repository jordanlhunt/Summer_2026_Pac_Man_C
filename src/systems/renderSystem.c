#include "../../include/systems/renderSystem.h"
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

    // Convert position to pixels rather than tiles
    float pixelX = (position->column + position->offsetX) * MAP_GRID_CELL_SIZE;
    float pixelY = (position->row + position->offsetY) * MAP_GRID_CELL_SIZE;
    SDL_Rect renderRect = {(int)pixelX, (int)pixelY, renderData->width,
                           renderData->height};
    SDL_SetRenderDrawColor(renderer, renderData->red, renderData->green,
                           renderData->blue, renderData->alpha);
    SDL_RenderFillRect(renderer, &renderRect);
  }
}

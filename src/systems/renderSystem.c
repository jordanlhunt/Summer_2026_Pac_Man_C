#include "../../include/systems/renderSystem.h"
void RenderSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  (void)renderer;
  (void)gameContext;
  int activeEntitiesCount = ECS_GetActiveEntitiesCount();
  for (RenderLayer layer = 0; layer < RENDERLAYER_NUMBER_OF_LAYERS; layer++) {
    for (int i = 0; i < activeEntitiesCount; i++) {
      Entity activeEntity = ECS_GetActiveEntity(i);
      if (ECS_HasComponents(activeEntity, COMPONENT_POSITION |
                                              COMPONENT_RENDERABLE) == false) {
        continue;
      }
      Renderable *renderData = ECS_GetRenderable(activeEntity);
      // Only render entities on the correct layer
      if (renderData->renderLayer != layer) {
        continue;
      }
      // Draw Based on component Type
      if (ECS_HasComponent(activeEntity, COMPONENT_PLAYER_CONTROLLED)) {
        GraphicsDrawPlayer(renderer, activeEntity, gameContext);
      } else if (ECS_HasComponent(activeEntity, COMPONENT_GHOST)) {
        GraphicsDrawGhost(renderer, activeEntity, gameContext);
      } else if (ECS_HasComponent(activeEntity, COMPONENT_EDIBLE)) {
        GraphicsDrawEdible(renderer, activeEntity);
      } else {
        Position *position = ECS_GetPosition(activeEntity);
        SDL_Rect sourceRectangle = {
            (int)((position->column + position->offsetX) * MAP_GRID_CELL_SIZE),
            (int)((position->row + position->offsetY) * MAP_GRID_CELL_SIZE),
            renderData->width, renderData->height};
        SDL_SetRenderDrawColor(renderer, renderData->red, renderData->green,
                               renderData->blue, renderData->alpha);
        SDL_RenderFillRect(renderer, &sourceRectangle);
      }
    }
  }
}

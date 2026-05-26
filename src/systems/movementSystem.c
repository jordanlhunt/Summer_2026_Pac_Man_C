#include "../../include/systems/movementSystem.h"
void MovementSystem(GameContext *gameContext, SDL_Renderer *renderer)
{
  int activeEntitieCount = ECS_GetActiveEntitiesCount();
  for (int i = 0; i < activeEntitieCount; i++)
  {
    Entity activeEntity = ECS_GetActiveEntity(i);
    if (ECS_HasComponents(activeEntity,
                          COMPONENT_POSITION | COMPONENT_VELOCITY) == false)
    {
      continue;
    }
    Position *position = ECS_GetPosition(activeEntity);
    Velocity *velocity = ECS_GetVelocity(activeEntity);
    if (velocity->deltaRow == 0 && velocity->deltaColumn == 0)
    {
      continue;
    }
    // tilesPersecond is 10.0 and deltaTime should be 0.016 (one frame at 60FPS)
    float distanceToMoveEntity =
        velocity->tilesPerSecond * gameContext->deltaTime;
    // Advance sub-tile offset and move X/Y pixels
    position->offsetX += velocity->deltaColumn * distanceToMoveEntity;
    position->offsetY += velocity->deltaRow * distanceToMoveEntity;
    // Check if entity cross threshold into next column
    if (position->offsetX >= 1.0f)
    {
      int nextColumn = position->column + 1;
      if (nextColumn < MAP_COLUMNS)
      {
        MapTile nextTile =
            GetMapTile(&gameContext->levelData, position->row, nextColumn);
        if (nextTile != TILE_WALL && (nextTile != TILE_GHOST_DOOR || ECS_HasComponent(activeEntity, COMPONENT_GHOST)))
        {
          position->column = nextColumn;
        }
      }
      position->offsetX -= 1.0f;
    }
    else if (position->offsetX <= -1.0f)
    {
      int nextColumn = position->column - 1;
      if (nextColumn >= 0)
      {
        MapTile nextTile = GetMapTile(&gameContext->levelData, position->row, nextColumn);
        if (nextTile != TILE_WALL &&
            (nextTile != TILE_GHOST_DOOR ||
             ECS_HasComponent(activeEntity, COMPONENT_GHOST)))
        {
          position->column = nextColumn;
        }
      }
      position->offsetX += 1.0f;
    }
    if (position->offsetY >= 1.0f)
    {
      int nextRow = position->row + 1;
      if (nextRow < MAP_ROWS)
      {
        MapTile nextTile = GetMapTile(&gameContext->levelData, nextRow, position->column);
        if (nextTile != TILE_WALL &&
            (nextTile != TILE_GHOST_DOOR || ECS_HasComponent(activeEntity, COMPONENT_GHOST)))
        {
          position->row = nextRow;
        }
        position->offsetY -= 1.0f;
      }
      else if (position->offsetY <= -1.0f)
      {
        int nextRow = position->row - 1;
        if (nextRow >= 0)
        {
          MapTile nextTile = GetMapTile(&gameContext->levelData, nextRow, position->column);
          if (nextTile != TILE_WALL &&
              (nextTile != TILE_GHOST_DOOR || ECS_HasComponent(activeEntity, COMPONENT_GHOST)))
          {
            position->row = nextRow;
          }
        }
        position->offsetY += 1.0f;
      }
      if (ECS_HasComponent(activeEntity, COMPONENT_PLAYER_CONTROLLED))
      {
        printf("[movement.c] - player Row = %d, player Column = %d\n",
               position->row, position->column);
      }
    }
  }

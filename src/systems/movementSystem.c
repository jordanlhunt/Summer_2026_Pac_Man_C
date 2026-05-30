#include "../../include/systems/movementSystem.h"
void MovementSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  int activeEntityCount = ECS_GetActiveEntitiesCount();
  for (int i = 0; i < activeEntityCount; i++) {
    Entity activeEntity = ECS_GetActiveEntity(i);
    if (ECS_HasComponents(activeEntity,
                          COMPONENT_POSITION | COMPONENT_VELOCITY) == false) {
      continue;
    }
    Position *position = ECS_GetPosition(activeEntity);
    Velocity *velocity = ECS_GetVelocity(activeEntity);
    if (velocity->deltaRow == 0 && velocity->deltaColumn == 0) {
      continue;
    }
    bool isPlayer = ECS_HasComponent(activeEntity, COMPONENT_PLAYER_CONTROLLED);
    bool isGhost = ECS_HasComponents(activeEntity, COMPONENT_GHOST);
    // tilesPersecond is 10.0 and deltaTime should be 0.016 (one frame at 60FPS)
    float distanceToMoveEntity =
        velocity->tilesPerSecond * gameContext->deltaTime;

    // Block player before moving into a wall
    if (isPlayer) {
      if (IsCenteredOnTile(position)) {
        int nextRow = position->row + velocity->deltaRow;
        int nextColumn = position->column + velocity->deltaColumn;
        MapTile nextTile =
            GetMapTile(&gameContext->levelData, nextRow, nextColumn);
        if (nextTile == TILE_WALL || nextTile == TILE_GHOST_DOOR) {
          velocity->deltaRow = 0;
          velocity->deltaColumn = 0;
          position->offsetX = 0.0f;
          position->offsetY = 0.0f;
          continue;
        }
      }
    }
    // Advance sub-tile offset and move X/Y pixels
    position->offsetX += velocity->deltaColumn * distanceToMoveEntity;
    position->offsetY += velocity->deltaRow * distanceToMoveEntity;
    // -- Right
    // Check if entity cross threshold into next column
    if (position->offsetX >= TILE_SIZE) {
      int nextColumn = position->column + 1;
      bool isBlocked = true;
      if (nextColumn < MAP_COLUMNS) {
        MapTile nextTile =
            GetMapTile(&gameContext->levelData, position->row, nextColumn);
        if (nextTile != TILE_WALL && (nextTile != TILE_GHOST_DOOR || isGhost)) {
          position->column = nextColumn;
          isBlocked = false;
        }
      }
      // Don't bounce off walls
      if (isBlocked && isPlayer) {
        velocity->deltaRow = 0;
        velocity->deltaColumn = 0;
        position->offsetX = 0.0f;
      } else {
        position->offsetX -= TILE_SIZE;
      }
    }
    // LEFT
    else if (position->offsetX <= -TILE_SIZE) {
      int nextColumn = position->column - 1;
      bool isBlocked = true;
      if (nextColumn >= 0) {
        MapTile nextTile =
            GetMapTile(&gameContext->levelData, position->row, nextColumn);
        if (nextTile != TILE_WALL && (nextTile != TILE_GHOST_DOOR || isGhost)) {
          position->column = nextColumn;
          isBlocked = false;
        }
      } // Don't bounce off walls
      if (isBlocked && isPlayer) {
        velocity->deltaRow = 0;
        velocity->deltaColumn = 0;
        position->offsetX = 0.0f;
      } else {
        position->offsetX += TILE_SIZE;
      }
    }
    // Down
    if (position->offsetY >= TILE_SIZE) {
      int nextRow = position->row + 1;
      bool isBlocked = true;
      if (nextRow < MAP_ROWS) {
        MapTile nextTile =
            GetMapTile(&gameContext->levelData, nextRow, position->column);
        if (nextTile != TILE_WALL && (nextTile != TILE_GHOST_DOOR || isGhost)) {
          position->row = nextRow;
          isBlocked = false;
        }
      }
      // Don't bounce off walls
      if (isBlocked && isPlayer) {
        velocity->deltaRow = 0;
        velocity->deltaColumn = 0;
        position->offsetY = 0.0f;
      } else {
        position->offsetY -= TILE_SIZE;
      }
    }
    // Up
    else if (position->offsetY <= -TILE_SIZE) {
      int nextRow = position->row - 1;
      bool isBlocked = true;
      if (nextRow >= 0) {
        MapTile nextTile =
            GetMapTile(&gameContext->levelData, nextRow, position->column);
        if (nextTile != TILE_WALL && (nextTile != TILE_GHOST_DOOR || isGhost)) {
          position->row = nextRow;
          isBlocked = false;
        }
      }
      // Don't bounce off walls
      if (isBlocked && isPlayer) {
        velocity->deltaRow = 0;
        velocity->deltaColumn = 0;
        position->offsetY = 0.0f;
      } else {
        position->offsetY += TILE_SIZE;
      }
    }
    if (isPlayer) {
      printf("[movement.c] - player Row = %d, player Column = %d\n",
             position->row, position->column);
    }
  }
}

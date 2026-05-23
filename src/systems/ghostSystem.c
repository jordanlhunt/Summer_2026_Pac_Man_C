// TODO: Create a System that handles Ghosts doing stuff.
#include "../../include/systems/ghostSystem.h"

static int DistanceSquared(int row1, int column1, int row2, int column2) {
  int distanceSquared = 0;
  int deltaRow = row2 - row1;
  int deltaColumn = column2 - column1;
  distanceSquared = (deltaRow * deltaRow) + (deltaColumn * deltaColumn);
  return distanceSquared;
}

static int DirectionToDeltaRow(Direction direction) {
  if (direction == UP) {
    return -1;
  } else if (direction == DOWN) {
    return 1;
  } else {
    return 0;
  }
}

static int DirectionToDeltaColumn(Direction direction) {
  if (direction == LEFT) {
    return -1;
  } else if (direction == RIGHT) {
    return 1;
  } else {
    return 0;
  }
}

static Direction OppositeDirection(Direction direction) {
  switch (direction) {
  case UP:
    return DOWN;
  case DOWN:
    return UP;
  case LEFT:
    return RIGHT;
  case RIGHT:
    return LEFT;
  default:
    return ZERO_DIRECTION;
  }
}

static void MoveGhostTowardTarget(Entity ghostEntity, int targetRow,
                                  int targetColumn, LevelData *levelData) {
  Position *position = ECS_GetPosition(ghostEntity);
  Velocity *velocity = ECS_GetVelocity(ghostEntity);
  Ghost *ghost = ECS_GetGhost(ghostEntity);
  // Testing Purposes
  if (ghost->ghostType != GHOSTTYPE_BLINKY) {
    return;
  }
  Direction directions[4] = {UP, DOWN, LEFT, RIGHT};
  Direction directionToTarget = ZERO_DIRECTION;
  int bestDistanceToTarget = INT_MAX;
  for (int i = 0; i < (sizeof(directions) / sizeof(directions[0])); i++) {
    Direction candidateDirection = directions[i];
    // No backwards movement is allowed for ghosts
    if (candidateDirection == OppositeDirection(ghost->currentDirection)) {
      continue;
    }
    int newRow = position->row + DirectionToDeltaRow(candidateDirection);
    int newColumn =
        position->column + DirectionToDeltaColumn(candidateDirection);
    // Can't move through walls
    MapTile tileAheadOfGhost = GetMapTile(levelData, newRow, newColumn);
    if (tileAheadOfGhost == TILE_WALL) {
      continue;
    }
    if (tileAheadOfGhost == TILE_GHOST_DOOR) {
      continue;
    }
    int distanceSquared =
        DistanceSquared(targetRow, targetColumn, newRow, newColumn);
    if (distanceSquared < bestDistanceToTarget) {
      bestDistanceToTarget = distanceSquared;
      directionToTarget = candidateDirection;
    }
  }
  if (directionToTarget != ZERO_DIRECTION) {
    ghost->currentDirection = directionToTarget;
    velocity->deltaRow = DirectionToDeltaRow(directionToTarget);
    velocity->deltaColumn = DirectionToDeltaColumn(directionToTarget);
  }
}
void GhostSystem(GameContext *gameContext, SDL_Renderer *renderer) {
  int activeEntitiesCount = ECS_GetActiveEntitiesCount();
  for (int i = 0; i < activeEntitiesCount; i++) {
    Entity activeEntity = ECS_GetActiveEntity(i);
    if (ECS_HasComponents(activeEntity, COMPONENT_GHOST | COMPONENT_POSITION |
                                            COMPONENT_VELOCITY) == false) {
      continue;
    }
    Ghost *ghost = ECS_GetGhost(activeEntity);
    if (ghost->ghostMode == GHOSTMODE_SCATTER) {
      MoveGhostTowardTarget(activeEntity, ghost->scatterTargetRow,
                            ghost->scatterTargetColumn,
                            &gameContext->levelData);
    }
    // TODO: ADD CHASE, FRIGHTENED, and EATEN
  }
}

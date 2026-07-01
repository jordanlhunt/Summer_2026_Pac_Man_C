#ifndef ENTITY_UTILS_H
#define ENTITY_UTILS_H

#include "common.h"
#include "ecs/components.h"

#define PLAYER_TURN_TOLERANCE 0.5f
#define GHOST_TURN_TOLERANCE 0.04f

static inline bool IsPlayerCentered(Position *entityPosition) {
  return fabsf(entityPosition->offsetX) < PLAYER_TURN_TOLERANCE &&
         fabsf(entityPosition->offsetY) < PLAYER_TURN_TOLERANCE;
}

static inline bool IsGhostCentered(Position *entityPosition) {
  return fabsf(entityPosition->offsetX) < GHOST_TURN_TOLERANCE &&
         fabsf(entityPosition->offsetY) < GHOST_TURN_TOLERANCE;
}

#endif


#ifndef ENTITY_UTILS_H
#define ENTITY_UTILS_H

#include "common.h"
#include "ecs/components.h"

#define TURN_TOLERANCE                                                         \
  .4f // This is the arcade Turn Tolerance so I'll use it until it doesn't feel
      // good
static inline bool IsCenteredOnTile(Position *entityPosition) {
  return fabsf(entityPosition->offsetX) < TURN_TOLERANCE &&
         fabsf(entityPosition->offsetY) < TURN_TOLERANCE;
}

#endif /* ENTITY_UTILS_H */

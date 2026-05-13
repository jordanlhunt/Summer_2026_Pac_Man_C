#include "../../include/ecs/ecs.h"
#include <string.h>
// Static/Persistent Variables
static Position staticPositions[MAX_ENTITIES];
static Velocity staticVelocities[MAX_ENTITIES];
static Renderable staticRenderables[MAX_ENTITIES];
static PlayerControlled staticPlayerControlledEntities[MAX_ENTITIES];
// Bitmask to keep track of what components has
static uint32_t staticComponentMasks[MAX_ENTITIES];
// Entity Pool
static Entity staticNextAvailableSlot = 1;
static bool staticEntitySlotUsed[MAX_ENTITIES];
// System Tracker
static System staticSystems[MAX_SYSTEMS];
static int staticSystemsCounter = 0;
void ECS_Initialize() {
  memset(staticComponentMasks, 0, sizeof(staticComponentMasks));
  memset(staticEntitySlotUsed, 0, sizeof(staticEntitySlotUsed));
  memset(staticPositions, 0, sizeof(staticPositions));
  memset(staticVelocities, 0, sizeof(staticVelocities));
  memset(staticRenderables, 0, sizeof(staticRenderables));
  memset(staticPlayerControlledEntities, 0,
         sizeof(staticPlayerControlledEntities));
  staticSystemsCounter = 0;
  staticNextAvailableSlot = 1;
}
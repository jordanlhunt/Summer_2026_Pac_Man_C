#include "../../include/ecs/ecs.h"
#include <stdbool.h>
#include <string.h>
// Static/Persistent Variables
static Position staticPositions[MAX_ENTITIES];
static Velocity staticVelocities[MAX_ENTITIES];
static Renderable staticRenderables[MAX_ENTITIES];
static PlayerControlled staticPlayerControlledEntities[MAX_ENTITIES];
static GameContext *globalGameContext = NULL;
static SDL_Renderer *globalSDLRenderer = NULL;
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
Entity ECS_CreateEntity() {
  for (Entity i = staticNextAvailableSlot; i < MAX_ENTITIES; i++) {
    if (!staticEntitySlotUsed[i]) {
      staticEntitySlotUsed[i] = true;
      staticComponentMasks[i] = COMPONENT_NONE;
      staticNextAvailableSlot = i + 1;
      return i;
    }
  }
  return 0;
}
void ECS_DestroyEntity(Entity entity) {
  if (entity == 0 || entity >= MAX_ENTITIES) {
    return;
  }
  staticEntitySlotUsed[entity] = false;
  staticComponentMasks[entity] = COMPONENT_NONE;
}
bool ECS_HasComponent(Entity entity, ComponentType componentType) {
  bool hasComponent = false;
  if ((staticComponentMasks[entity] & componentType) != 0) {
    hasComponent = true;
  }
  return hasComponent;
}
void ECS_AddComponent(Entity entity, ComponentType componentType) {
  staticComponentMasks[entity] |= componentType;
}
void ECS_RemoveComponent(Entity entity, ComponentType componentType) {
  staticComponentMasks[entity] &= ~componentType;
}
Position *ECS_GetPosition(Entity entity) {
  Position *currentPosition = NULL;
  if (ECS_HasComponent(entity, COMPONENT_POSITION)) {
    currentPosition = &staticPositions[entity];
  }
  return currentPosition;
}
Velocity *ECS_GetVelocity(Entity entity) {
  Velocity *currentVelocity = NULL;
  if (ECS_HasComponent(entity, COMPONENT_VELOCITY)) {
    currentVelocity = &staticVelocities[entity];
  }
  return currentVelocity;
}
Renderable *ECS_GetRenderable(Entity entity) {
  Renderable *renderData = NULL;
  if (ECS_HasComponent(entity, COMPONENT_RENDERABLE)) {
    renderData = &staticRenderables[entity];
  }
  return renderData;
}
PlayerControlled *ECS_GetPlayerControlled(Entity entity) {
  PlayerControlled *playerControlled = NULL;
  if (ECS_HasComponent(entity, COMPONENT_PLAYER_INPUT)) {
    playerControlled = &staticPlayerControlledEntities[entity];
  }
  return playerControlled;
}
void ECS_RegisterSystem(System system) {
  if (staticSystemsCounter < MAX_SYSTEMS) {
    staticSystems[staticSystemsCounter++] = system;
  }
}
void ECS_Update() {
  for (int i = 0; i < staticSystemsCounter; i++) {
    staticSystems[i]();
  }
}

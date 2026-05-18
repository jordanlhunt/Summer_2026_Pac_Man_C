#include "../../include/ecs/ecs.h"
// Static/Persistent Variables
static Position staticPositions[MAX_ENTITIES];
static Velocity staticVelocities[MAX_ENTITIES];
static Renderable staticRenderables[MAX_ENTITIES];
static PlayerControlled staticPlayerControlledEntities[MAX_ENTITIES];
static Entity staticActiveEntities[MAX_ENTITIES];
static Edible staticEdibles[MAX_ENTITIES];
// Bitmask to keep track of what components has
static uint32_t staticComponentMasks[MAX_ENTITIES];
// Entity Pool
static bool staticEntitySlotUsed[MAX_ENTITIES];
// System Tracker
static System staticSystems[MAX_SYSTEMS];
static int staticSystemsCounter = 0;
static int staticActiveCount = 0;
void ECS_Initialize() {
  memset(staticComponentMasks, 0, sizeof(staticComponentMasks));
  memset(staticEntitySlotUsed, 0, sizeof(staticEntitySlotUsed));
  memset(staticPositions, 0, sizeof(staticPositions));
  memset(staticVelocities, 0, sizeof(staticVelocities));
  memset(staticRenderables, 0, sizeof(staticRenderables));
  memset(staticPlayerControlledEntities, 0,
         sizeof(staticPlayerControlledEntities));
  memset(staticActiveEntities, 0, sizeof(staticActiveEntities));
  memset(staticEdibles, 0, sizeof(staticEdibles));
  staticSystemsCounter = 0;
  staticActiveCount = 0;
}
Entity ECS_CreateEntity() {
  for (Entity i = 1; i < MAX_ENTITIES; i++) {
    if (!staticEntitySlotUsed[i]) {
      staticEntitySlotUsed[i] = true;
      staticComponentMasks[i] = COMPONENT_NONE;
      staticActiveEntities[staticActiveCount] = i;
      staticActiveCount++;
      return i;
    }
  }
  printf("[ecs.c] - ECS_CreateEntity: No available entity slots!\n");
  return 0;
}
void ECS_DestroyEntity(Entity entity) {
  if (entity == 0 || entity >= MAX_ENTITIES) {
    return;
  }
  staticEntitySlotUsed[entity] = false;
  staticComponentMasks[entity] = COMPONENT_NONE;
  // Remove the entity from the active list
  for (int i = 0; i < staticActiveCount; i++) {
    // swap the last active entity into the position of the destroyed entity
    staticActiveEntities[i] = staticActiveEntities[staticActiveCount - 1];
    // Zero out the last slot
    staticActiveEntities[staticActiveCount - 1] = 0;
    staticActiveCount--;
    break;
  }
}
bool ECS_HasComponent(Entity entity, ComponentType componentType) {
  bool hasComponent = false;
  if ((staticComponentMasks[entity] & componentType) != 0) {
    hasComponent = true;
  }
  return hasComponent;
}
bool ECS_HasComponents(Entity entity, ComponentType componentType) {
  bool hasComponents = false;
  if ((staticComponentMasks[entity] & componentType) == componentType) {
    hasComponents = true;
  }
  return hasComponents;
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
  if (ECS_HasComponent(entity, COMPONENT_PLAYER_CONTROLLED)) {
    playerControlled = &staticPlayerControlledEntities[entity];
  }
  return playerControlled;
}
void ECS_RegisterSystem(System system) {
  if (staticSystemsCounter < MAX_SYSTEMS) {
    staticSystems[staticSystemsCounter++] = system;
  }
}
void ECS_Update(struct GameContext *gameContext, SDL_Renderer *renderer) {
  for (int i = 0; i < staticSystemsCounter; i++) {
    staticSystems[i](gameContext, renderer);
  }
}
int ECS_GetActiveEntitiesCount() { return staticActiveCount; }
Entity ECS_GetActiveEntity(int index) {
  if (index >= 0 && index < staticActiveCount) {
    return staticActiveEntities[index];
  }
  printf("[ecs.c - ECS_GetActiveEntity] - Invalid index");
  return 0;
}

Edible *ECS_GetEdible(Entity entity) {
  Edible *edible = NULL;
  if (ECS_HasComponent(entity, COMPONENT_EDIBLE)) {
    return &staticEdibles[entity];
  }
  return edible;
}

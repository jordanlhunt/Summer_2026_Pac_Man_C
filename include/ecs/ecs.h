#ifndef ECS_H
#define ECS_H
#include "../common.h"
#include "components.h"
#include "entity.h"
#define MAX_ENTITIES                                                           \
  512 // 512 is double the size of all the maximum of entities the game may have
#define MAX_SYSTEMS 32
// Forward Declare
struct GameContext;
struct SDL_Renderer;
// Component type
typedef enum ComponentType {
  COMPONENT_NONE = 0,
  COMPONENT_POSITION = 1 << 0,
  COMPONENT_VELOCITY = 1 << 1,
  COMPONENT_RENDERABLE = 1 << 2,
  COMPONENT_PLAYER_CONTROLLED = 1 << 3,
} ComponentType;
// Entity Coordinator (I don't like the word 'manager' because of MEGACORPs have
// polluted it)
void ECS_Initialize();
void ECS_DestroyEntity(Entity entity);
Entity ECS_CreateEntity();
// Component Add/Remove
bool ECS_HasComponent(Entity entity, ComponentType componentType);
void ECS_AddComponent(Entity entity, ComponentType componentType);
void ECS_RemoveComponent(Entity entity, ComponentType componentType);
// Getters and Setter
Position *ECS_GetPosition(Entity entity);
Velocity *ECS_GetVelocity(Entity entity);
Renderable *ECS_GetRenderable(Entity entity);
PlayerControlled *ECS_GetPlayerControlled(Entity entity);

// Function Pointer to register systems
typedef void (*System)(GameContext *gameContext, SDL_Renderer *renderer);
void ECS_RegisterSystem(System system);
void ECS_Update(GameContext *gameContext, SDL_Renderer *renderer);

#endif

#include "../../include/gameinitialization.h"
bool InitializeSDL(SDLContext *sdlContext) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("[gameinitialization.c] - SDL failed to initialize: %s\n",
           SDL_GetError());
    return false;
  }
  sdlContext->gameWindow = SDL_CreateWindow(
      "Hac-Man", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
      SCREEN_HEIGHT, SDL_WINDOW_HIDDEN);
  sdlContext->renderer =
      SDL_CreateRenderer(sdlContext->gameWindow, -1, SDL_RENDERER_ACCELERATED);
  return true;
}
bool InitializePlayer(GameContext *gameContext, Entity player) {
  ECS_AddComponent(player, COMPONENT_POSITION | COMPONENT_VELOCITY |
                               COMPONENT_RENDERABLE |
                               COMPONENT_PLAYER_CONTROLLED);
  bool isSpawnLocationFound = false;
  for (int row = 0; row < MAP_ROWS; row++) {
    for (int column = 0; column < MAP_COLUMNS; column++) {
      if (GetMapTile(&gameContext->levelData, row, column) == TILE_PLAYER) {
        Position *playerPosition = ECS_GetPosition(player);
        playerPosition->row = row;
        gameContext->playerSpawnRow = row;
        playerPosition->column = column;
        gameContext->playerSpawnColumn = column;
        SetMapTile(&gameContext->levelData, row, column, TILE_EMPTY);
        isSpawnLocationFound = true;
      }
    }
  }
  if (isSpawnLocationFound == false) {
    printf("[gameInitialization.c] - NO TILE_PLAYER spawn location found! \n");
    return false;
  }
  Velocity *velocity = ECS_GetVelocity(player);
  velocity->deltaRow = 0;
  velocity->deltaColumn = 0;
  velocity->tilesPerSecond = PLAYER_SPEED;
  Renderable *renderData = ECS_GetRenderable(player);
  renderData->red = 255;
  renderData->green = 255;
  renderData->blue = 0;
  renderData->alpha = 255;
  renderData->width = MAP_GRID_CELL_SIZE;
  renderData->height = MAP_GRID_CELL_SIZE;
  return true;
}
bool InitializeGhosts(GameContext *gameContext) {
  struct {
    GhostType ghostType;
    int red;
    int green;
    int blue;
    int scatterRow;
    int scatterColumn;
    int ghostHouseReleaseThreshold;
    GhostMode initialMode;
  } ghostData[GHOST_COUNT] = {
      {GHOSTTYPE_BLINKY, 255, 0, 0, 0, MAP_COLUMNS - 1, 0, GHOSTMODE_SCATTER},
      {GHOSTTYPE_PINKY, 255, 184, 255, 0, 0, PINKY_RELEASE_THRESHOLD,
       GHOSTMODE_IN_GHOSTHOUSE},
      {GHOSTTYPE_INKY, 0, 255, 255, MAP_ROWS - 1, MAP_COLUMNS - 1,
       INKY_RELEASE_THRESHOLD, GHOSTMODE_IN_GHOSTHOUSE},
      {GHOSTTYPE_CLYDE, 255, 184, 82, MAP_ROWS - 1, 0, CLYDE_RELEASE_THRESHOLD,
       GHOSTMODE_IN_GHOSTHOUSE},
  };
  for (int i = 0; i < GHOST_COUNT; i++) {
    Entity newEntity = ECS_CreateEntity();
    gameContext->ghostsEntities[i] = newEntity;
    ECS_AddComponent(newEntity, COMPONENT_POSITION | COMPONENT_VELOCITY |
                                    COMPONENT_RENDERABLE | COMPONENT_GHOST);
    Ghost *ghost = ECS_GetGhost(newEntity);
    ghost->ghostType = ghostData[i].ghostType;
    ghost->ghostMode = ghostData[i].initialMode;
    ghost->currentDirection = ZERO_DIRECTION;
    ghost->scatterTargetRow = ghostData[i].scatterRow;
    ghost->scatterTargetColumn = ghostData[i].scatterColumn;
    Velocity *velocity = ECS_GetVelocity(newEntity);
    velocity->deltaRow = 0;
    velocity->deltaColumn = 0;
    velocity->tilesPerSecond = GHOST_SPEED;
    Renderable *renderData = ECS_GetRenderable(newEntity);
    renderData->red = ghostData[i].red;
    renderData->blue = ghostData[i].blue;
    renderData->green = ghostData[i].green;
    renderData->alpha = 255;
    renderData->width = MAP_GRID_CELL_SIZE;
    renderData->height = MAP_GRID_CELL_SIZE;
  }
  return true;
}
void InitializeSystems() {
  ECS_RegisterSystem(InputSystem);
  ECS_RegisterSystem(MovementSystem);
  ECS_RegisterSystem(CollisionSystem);
  ECS_RegisterSystem(GhostSystem);
  ECS_RegisterSystem(RenderSystem);
}
void Shutdown(SDLContext *sdlContext) {
  SDL_DestroyRenderer(sdlContext->renderer);
  SDL_DestroyWindow(sdlContext->gameWindow);
  SDL_Quit();
}

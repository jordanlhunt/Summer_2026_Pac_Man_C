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
  if (InitializeGraphics(sdlContext->renderer, SOURCESPRITESHEETPNG) == false) {
    printf("[gameinitialization.c] - SDL failed to initialize graphics: %s\n",
           SDL_GetError());
    InitializeTTF();
  }
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
  renderData->renderLayer = RENDERLAYER_PLAYER;
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
    int spawnRow;
    int spawnColumn;
    GhostMode initialMode;
  } ghostData[GHOST_COUNT] = {
      // Designated initializers for accuracy and clarity, I like this method
      // [https://gcc.gnu.org/onlinedocs/gcc/Designated-Inits.html]
      {
          .ghostType = GHOSTTYPE_BLINKY,
          .red = 255,
          .green = 0,
          .blue = 0,
          .scatterRow = 0,
          .scatterColumn = MAP_COLUMNS - 1,
          .ghostHouseReleaseThreshold = 0,
          .spawnRow = BLINKY_SPAWN_ROW,
          .spawnColumn = BLINKY_SPAWN_COLUMN,
          .initialMode = GHOSTMODE_SCATTER,
      },
      {
          .ghostType = GHOSTTYPE_PINKY,
          .red = 255,
          .green = 184,
          .blue = 255,
          .scatterRow = 0,
          .scatterColumn = 0,
          .ghostHouseReleaseThreshold = RELEASE_THRESHOLD_PINKY,
          .spawnRow = PINKY_SPAWN_ROW,
          .spawnColumn = PINKY_SPAWN_COLUMN,
          .initialMode = GHOSTMODE_IN_GHOSTHOUSE,
      },
      {
          .ghostType = GHOSTTYPE_INKY,
          .red = 0,
          .green = 255,
          .blue = 255,
          .scatterRow = MAP_ROWS - 1,
          .scatterColumn = MAP_COLUMNS - 1,
          .ghostHouseReleaseThreshold = RELEASE_THRESHOLD_INKY,
          .spawnRow = INKY_SPAWN_ROW,
          .spawnColumn = INKY_SPAWN_COLUMN,
          .initialMode = GHOSTMODE_IN_GHOSTHOUSE,
      },
      {

          .ghostType = GHOSTTYPE_CLYDE,
          .red = 255,
          .green = 184,
          .blue = 82,
          .scatterRow = MAP_ROWS - 1,
          .scatterColumn = 0,
          .ghostHouseReleaseThreshold = RELEASE_THRESHOLD_CLYDE,
          .spawnRow = CLYDE_SPAWN_ROW,
          .spawnColumn = CLYDE_SPAWN_COLUMN,
          .initialMode = GHOSTMODE_IN_GHOSTHOUSE,
      },
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
    ghost->exitGhostHouseThreshold = ghostData[i].ghostHouseReleaseThreshold;
    Velocity *velocity = ECS_GetVelocity(newEntity);
    velocity->deltaRow = 0;
    velocity->deltaColumn = 0;
    velocity->tilesPerSecond = GHOST_SPEED;
    Position *position = ECS_GetPosition(newEntity);
    position->row = ghostData[i].spawnRow;
    position->column = ghostData[i].spawnColumn;
    printf("[gameInitialization.c] - Ghost %d spawned at row=%d col=%d\n", i,
           position->row, position->column);
    Renderable *renderData = ECS_GetRenderable(newEntity);
    renderData->red = ghostData[i].red;
    renderData->blue = ghostData[i].blue;
    renderData->green = ghostData[i].green;
    renderData->alpha = 255;
    renderData->width = MAP_GRID_CELL_SIZE;
    renderData->height = MAP_GRID_CELL_SIZE;
    renderData->renderLayer = RENDERLAYER_GHOST;
  }
  return true;
}
void InitializeSystems() {
  ECS_RegisterSystem(InputSystem);
  ECS_RegisterSystem(MovementSystem);
  ECS_RegisterSystem(CollisionSystem);
  // ECS_RegisterSystem(GhostSystem);
  ECS_RegisterSystem(RenderSystem);
}
void Shutdown(SDLContext *sdlContext) {
  ShutdownGraphics();
  ShutdownTTF();
  SDL_DestroyRenderer(sdlContext->renderer);
  SDL_DestroyWindow(sdlContext->gameWindow);
  SDL_Quit();
}

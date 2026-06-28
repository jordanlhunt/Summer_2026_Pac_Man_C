#include "../../include/gameinitialization.h"
bool InitializeSDL(SDLContext *sdlContext, GameContext *gameContext) {
  if (sdlContext == NULL || gameContext == NULL) {
    return false;
  }
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("[gameinitialization.c] - SDL failed to initialize: %s\n",
           SDL_GetError());
    return false;
  }
  sdlContext->gameWindow = SDL_CreateWindow(
      "Hac-Man", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
      SCREEN_HEIGHT, SDL_WINDOW_HIDDEN);
  if (sdlContext->gameWindow == NULL) {
    printf("[InitializeSDL] SDL_CreateWindow failed: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }
  sdlContext->renderer =
      SDL_CreateRenderer(sdlContext->gameWindow, -1, SDL_RENDERER_ACCELERATED);
  if (sdlContext->renderer == NULL) {
    printf("[gameinitialization.c] - SDL_CreateRenderer failed: %s\n",
           SDL_GetError());
    SDL_DestroyWindow(sdlContext->gameWindow);
    SDL_Quit();
    return false;
  }
  SDL_RenderSetLogicalSize(sdlContext->renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  if (InitializeAudio(&gameContext->audioPlayer) == false) {
    SDL_DestroyRenderer(sdlContext->renderer);
    SDL_DestroyWindow(sdlContext->gameWindow);
    SDL_Quit();
    return false;
  }

  if (InitializeGraphics(sdlContext->renderer, SOURCESPRITESHEETPNG) == false) {
    printf("[gameinitialization.c] - SDL failed to initialize graphics: %s\n",
           SDL_GetError());
  }
  InitializeTTF();
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
void InitializeSystems() {
  ECS_RegisterSystem(InputSystem);
  ECS_RegisterSystem(MovementSystem);
  ECS_RegisterSystem(CollisionSystem);
  ECS_RegisterSystem(GhostSystem);
  ECS_RegisterSystem(RenderSystem);
}
void Shutdown(SDLContext *sdlContext, GameContext *gameContext) {
  ShutdownAudio(&gameContext->audioPlayer);
  ShutdownGraphics();
  ShutdownTTF();
  SDL_DestroyRenderer(sdlContext->renderer);
  SDL_DestroyWindow(sdlContext->gameWindow);
  SDL_Quit();
}

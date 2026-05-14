#include "../include/main.h"
int main(int argc, char* argv[]) {
  SDLContext sdlContext = {0};
  GameContext gameContext = {0};
  if (InitializeSDL(&sdlContext) == false) {
    return 1;
  }
  ECS_Initialize();
  InitializeSystems();
  LoadMap(&gameContext.levelData, PATH_TO_MAZE_FILE);
  InitializeGameContext(&gameContext);
  Entity player = ECS_CreateEntity();
  if (InitializePlayer(&gameContext, player) == false) {
    return 1;
  }
  gameContext.playerEntity = player;
  // Game Loop
  bool isQuit = false;
  Uint32 previousTime = SDL_GetTicks();
  SDL_Event sdl_event;
  SDL_ShowWindow(SDLContext.window);
  while (isQuit == false) {
    // Create a Delta Time for all the various Timers
    Uint32 currentTime = SDL_GetTicks();
    // Convert from Milliseconds to seconds
    float deltaTime = (currentTime - previousTime) / 1000.0f;
    previousTime = currentTime;
    while (SDL_PollEvent(&sdl_event) != 0) {
      if (sdl_event.type == SDL_QUIT) {
        isQuit = true;
      }
      handleEvent(&sdl_event, &gameContext);
    }
    if (gameContext.input.quitGame == true) {
      isQuit = true;
    }
    // Handle the Frightened Ghost Mode
    UpdateFrightenedModeTimer(&gameContext, deltaTime);
    SDL_SetRenderDrawColor(renderer, 100, 216, 107, 255);  // Matrix Green
    if (gameContext.isFrightenedGhostModeActive == true) {
      // Change the background color for visual feedback
      SDL_SetRenderDrawColor(renderer, 206, 32, 41, 255);  // Fire Engine Red
    }
    SDL_RenderClear(renderer);
    DrawMap(&gameContext.levelData, renderer);
    DrawPlayer(&gameContext, renderer);
    SDL_RenderPresent(renderer);
    delayFramerate(currentTime);
  }
  cleanup(renderer, window);
  return 0;
}
// Caps the game's execution speed to maintain a consistent 60 FPS
void delayFramerate(Uint32 startTime) {
  Uint32 elapsedTime = SDL_GetTicks() - startTime;
  if (elapsedTime < FRAMERATE_DELAY) {
    SDL_Delay(FRAMERATE_DELAY - elapsedTime);
  }
}
void UpdateFrightenedModeTimer(GameContext gameContext, float deltaTime) {
  if (gameContext.isFrightenedGhostModeActive == true) {
    gameContext.frightenedGhostModeTimer -= deltaTime;
    if (gameContext.frightenedGhostModeTimer <= 0.0) {
      gameContext.isFrightenedGhostModeActive = false;
      gameContext.frightenedGhostModeTimer = 0.0f;
      printf("[main.c] - Ghost Timer is 0, Ghost are no longer FRIGHTENED\n");
    }
  }
}

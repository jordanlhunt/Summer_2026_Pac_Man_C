#include "../include/main.h"
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  SDLContext sdlContext = {0};
  GameContext gameContext = {0};
  if (InitializeSDL(&sdlContext, &gameContext) == false) {
    return 1;
  }
  ECS_Initialize();
  InitializeSystems();
  InitializeGameContext(&gameContext);
  AudioPlayStartMusic(&gameContext.audioPlayer);
  // Game Loop
  bool isQuit = false;
  Uint32 previousTime = SDL_GetTicks();
  SDL_Event sdl_event;
  SDL_ShowWindow(sdlContext.gameWindow);
  while (isQuit == false) {
    // Create a Delta Time for all the various Timers
    Uint32 currentTime = SDL_GetTicks();
    // Convert from Milliseconds to seconds
    gameContext.deltaTime = (currentTime - previousTime) / 1000.0f;
    // Clamp deltaTime
    if (gameContext.deltaTime > MAX_DELTA_TIME) {
      gameContext.deltaTime = MAX_DELTA_TIME;
    }
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

    // State Machine
    switch (gameContext.currentGameState) {
    case GAMESTATE_TITLE: {
      // Press Spacebar to 'insert coin' to start the play session
      if (gameContext.input.pauseGame == true) {
        ResetGameRound(&gameContext);
        gameContext.currentGameState = GAMESTATE_PLAYING;
        gameContext.input.pauseGame = false;
      }
      break;
    }
    case GAMESTATE_PLAYING: {
      updateFrightenedModeTimer(&gameContext, gameContext.deltaTime);
      UpdateGhostTimer(&gameContext, gameContext.deltaTime);
      ECS_Update(&gameContext, sdlContext.renderer);
      break;
    }
    case GAMESTATE_GAME_OVER: {
      // Press Spacebar to insert another coin and reset the game
      if (gameContext.input.pauseGame == true) {
        InitializeGameContext(&gameContext);
        LoadMap(&gameContext.levelData, PATH_TO_MAZE_FILE,
                gameContext.ghostsEntities);
        Entity player = ECS_CreateEntity();
        InitializePlayer(&gameContext, player);
        gameContext.playerEntity = player;
        gameContext.currentGameState = GAMESTATE_TITLE;
        gameContext.input.pauseGame = false;
      }
      break;
    }
    default: {
      break;
    }
    }

    // Render and Update
    SDL_SetRenderDrawColor(
        sdlContext.renderer, 100, 149, 237,
        255); // XNA Cornflower Blue as an homage to my many failed attempts to
              // into game development even though I totally missed the boat and
              // this hobby will likely never be sustainable as a career. I wish
              // I didn't slack off in my youth, can't change the past only the
              // present. I'll find a game development job somewhere.

    SDL_RenderClear(sdlContext.renderer);
    switch (gameContext.currentGameState) {
    case GAMESTATE_TITLE: {
      DrawTitleScreen(sdlContext.renderer, &gameContext);
      break;
    }
    default: {
      break;
    }
    }
  }
  Shutdown(&sdlContext, &gameContext);
  return 0;
}
// Caps the game's execution speed to maintain a consistent 60 FPS
void DelayFramerate(Uint32 startTime) {
  Uint32 elapsedTime = SDL_GetTicks() - startTime;
  if (elapsedTime < FRAMERATE_DELAY) {
    SDL_Delay(FRAMERATE_DELAY - elapsedTime);
  }
}
void UpdateFrightenedModeTimer(GameContext *gameContext, float deltaTime) {
  if (gameContext->isFrightenedGhostModeActive == true) {
    gameContext->frightenedGhostModeTimer -= deltaTime;
    if (gameContext->frightenedGhostModeTimer <= 0.0) {
      gameContext->isFrightenedGhostModeActive = false;
      gameContext->frightenedGhostModeTimer = 0.0f;
      printf("[main.c] - Ghost Timer is 0, Ghost are no longer FRIGHTENED\n");
    }
  }
}

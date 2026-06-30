#include "../include/main.h"
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
// Caps the game's execution speed to maintain a consistent 60 FPS
void DelayFramerate(Uint32 startTime) {
  Uint32 elapsedTime = SDL_GetTicks() - startTime;
  if (elapsedTime < FRAMERATE_DELAY) {
    SDL_Delay(FRAMERATE_DELAY - elapsedTime);
  }
}
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
  LoadMap(&gameContext.levelData, PATH_TO_MAZE_FILE,
          gameContext.ghostsEntities);
  Entity player = ECS_CreateEntity();
  if (InitializePlayer(&gameContext, player) == false) {
    return 1;
  }
  gameContext.playerEntity = player;

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
    // Update
    switch (gameContext.currentGameState) {
    case GAMESTATE_TITLE: {
      break;
    }
    case GAMESTATE_PLAYING: {
      UpdateFrightenedModeTimer(&gameContext, gameContext.deltaTime);
      UpdateGhostTimer(&gameContext, gameContext.deltaTime);
      UpdateFruitTimer(&gameContext, gameContext.deltaTime);
      ECS_Update(&gameContext, sdlContext.renderer);
      break;
    }
    case GAMESTATE_DEATH_ANIMATION:{
      bool isDeathAnimaitonFinished = GraphicsUpdateDeathAnimation(gameContext.deltaTime);
      if(isDeathAnimaitonFinished==true){
        gameContext.playerLives -= 1;
              printf("[main.c] - Death animation finished. Lives remaining: %d\n",
               gameContext.playerLives);
               if(gameContext.playerLives <=0 ){
                TriggerGameOver(&gameContext);
               }
               else {
                ResetGameRound(&gameContext);
                gameContext.currentGameState =GAMESTATE_PLAYING;
               }
      }
      break;
    }
    case GAMESTATE_GAME_OVER: {
      break;
    }
    case GAMESTATE_PAUSED: {
      break;
    }
    default: {
      break;
    }
    }

    // Render
    SDL_SetRenderDrawColor(sdlContext.renderer, 0, 0, 0,
                           255); // Black background to arcade cabinet feel,
    SDL_RenderClear(sdlContext.renderer);
    switch (gameContext.currentGameState) {
    case GAMESTATE_TITLE: {
      DrawTitleScreen(sdlContext.renderer, &gameContext);
      break;
    }
    case GAMESTATE_PLAYING: {
      DrawMap(&gameContext.levelData, sdlContext.renderer);
      ECS_Draw(&gameContext, sdlContext.renderer);
      DrawUI(sdlContext.renderer, &gameContext);
      // A white dividing line for clarity sake
      SDL_SetRenderDrawColor(sdlContext.renderer, 255, 255, 255, 255);
      SDL_RenderDrawLine(sdlContext.renderer, 0, UI_BLACK_BAR_HEIGHT,
                         LOGICAL_WIDTH, UI_BLACK_BAR_HEIGHT);
      SDL_RenderDrawLine(
          sdlContext.renderer, 0, LOGICAL_HEIGHT - UI_BLACK_BAR_HEIGHT - 1,
          LOGICAL_WIDTH, LOGICAL_HEIGHT - UI_BLACK_BAR_HEIGHT - 1);
      break;
    }
     case GAMESTATE_DEATH_ANIMATION: {
      DrawMap(&gameContext.levelData, sdlContext.renderer);
      ECS_Draw(&gameContext, sdlContext.renderer);
      DrawUI(sdlContext.renderer, &gameContext);
      SDL_SetRenderDrawColor(sdlContext.renderer, 255, 255, 255, 255);
      SDL_RenderDrawLine(sdlContext.renderer, 0, UI_BLACK_BAR_HEIGHT,
                         LOGICAL_WIDTH, UI_BLACK_BAR_HEIGHT);
      SDL_RenderDrawLine(sdlContext.renderer, 0,
                         LOGICAL_HEIGHT - UI_BLACK_BAR_HEIGHT - 1,
                         LOGICAL_WIDTH,
                         LOGICAL_HEIGHT - UI_BLACK_BAR_HEIGHT - 1);
      break;
    }
    case GAMESTATE_GAME_OVER: {
      DrawMap(&gameContext.levelData, sdlContext.renderer);
      ECS_Draw(&gameContext, sdlContext.renderer);
      DrawGameOverScreen(sdlContext.renderer, &gameContext);
      break;
    }
    case GAMESTATE_PAUSED: {
      DrawMap(&gameContext.levelData, sdlContext.renderer);
      ECS_Draw(&gameContext, sdlContext.renderer);
      DrawPausedScreen(sdlContext.renderer);
      break;
    }
    default: {
      break;
    }
    }

    SDL_RenderPresent(sdlContext.renderer);
    DelayFramerate(currentTime);
  }
  Shutdown(&sdlContext, &gameContext);
  return 0;
}

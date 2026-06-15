#include "../../include/graphics.h"
#include "../../include/gamecontext.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>
SpriteSheet *globalSpriteSheet = NULL;
TTF_Font *globalFont = NULL;
// PAC-MAN Animation State
static float staticPacmanAnimationTimer = 0.0f;
static int staticPacmanCurrentFrame = 0;
// Ghost Animation State
static float staticGhostFrightTimer = 0.0f;
static float staticGhostFlashTimer = 0.0f;
static int staticGhostFlashFrame = 0;
static int staticGhostFrightFrame = 0;
bool InitializeGraphics(SDL_Renderer *renderer, const char *spriteSheetPath) {
  SDL_Surface *sourceSpriteSheetSurface = IMG_Load(spriteSheetPath);
  if (sourceSpriteSheetSurface == NULL) {
    printf("[graphics.c] - Failed to load sprite sheet: %s\n", IMG_GetError());
    return false;
  }
  // malloc spriteSheet
  globalSpriteSheet = malloc(sizeof(SpriteSheet));
  if (globalSpriteSheet == NULL) {
    SDL_FreeSurface(sourceSpriteSheetSurface);
    printf("[graphics.c] - Failed to malloc spritesheet\n");
    return false;
  }
  // Load the source sheet with all the textures
  globalSpriteSheet->texture =
      SDL_CreateTextureFromSurface(renderer, sourceSpriteSheetSurface);
  SDL_FreeSurface(sourceSpriteSheetSurface);
  if (globalSpriteSheet->texture == NULL) {
    printf("[graphics.c] - Failed to create globalSpriteSheet textue: %s\n",
           SDL_GetError());
    return false;
  }
  /* --  Get all of the sprites from the sheet --  */
  // Maze Tiles
  globalSpriteSheet->dot =
      (SDL_Rect){8, 8, SMALL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->powerPellet =
      (SDL_Rect){8, 24, SMALL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->ghostDoor = (SDL_Rect){104, 101, 2, 2};
  // Pac-Man movement, 3 frame chop in all directions
  globalSpriteSheet->pacmanRight[0] =
      (SDL_Rect){456, 0, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanRight[1] =
      (SDL_Rect){472, 0, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanRight[2] =
      (SDL_Rect){488, 0, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanLeft[0] =
      (SDL_Rect){456, 16, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanLeft[1] =
      (SDL_Rect){472, 16, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanLeft[2] =
      (SDL_Rect){488, 0, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanUp[0] =
      (SDL_Rect){456, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanUp[1] =
      (SDL_Rect){472, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanUp[2] =
      (SDL_Rect){488, 0, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanDown[0] =
      (SDL_Rect){456, 48, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanDown[1] =
      (SDL_Rect){472, 48, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->pacmanDown[2] =
      (SDL_Rect){488, 0, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // Pac-Man death death animation
  for (int i = 0; i < PACMAN_DEATH_ANIMATION_FRAMES; i++) {
    globalSpriteSheet->pacmanDeath[i] =
        (SDL_Rect){504 + (i * GENERAL_SPRITE_SIZE), 0, GENERAL_SPRITE_SIZE,
                   GENERAL_SPRITE_SIZE};
  }
  // Ghost Animations
  // Movement
  // BLINKY
  globalSpriteSheet->ghostNormal[GHOSTTYPE_BLINKY]
      .ghostDirections[RIGHT]
      .ghostFrames[0] =
      (SDL_Rect){456, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_BLINKY]
      .ghostDirections[RIGHT]
      .ghostFrames[1] =
      (SDL_Rect){472, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_BLINKY]
      .ghostDirections[LEFT]
      .ghostFrames[0] =
      (SDL_Rect){488, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_BLINKY]
      .ghostDirections[LEFT]
      .ghostFrames[1] =
      (SDL_Rect){504, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_BLINKY]
      .ghostDirections[UP]
      .ghostFrames[0] =
      (SDL_Rect){520, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_BLINKY]
      .ghostDirections[UP]
      .ghostFrames[1] =
      (SDL_Rect){536, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_BLINKY]
      .ghostDirections[DOWN]
      .ghostFrames[0] =
      (SDL_Rect){552, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_BLINKY]
      .ghostDirections[DOWN]
      .ghostFrames[1] =
      (SDL_Rect){568, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // PINKY
  globalSpriteSheet->ghostNormal[GHOSTTYPE_PINKY]
      .ghostDirections[RIGHT]
      .ghostFrames[0] =
      (SDL_Rect){456, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_PINKY]
      .ghostDirections[RIGHT]
      .ghostFrames[1] =
      (SDL_Rect){472, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_PINKY]
      .ghostDirections[LEFT]
      .ghostFrames[0] =
      (SDL_Rect){488, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_PINKY]
      .ghostDirections[LEFT]
      .ghostFrames[1] =
      (SDL_Rect){504, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_PINKY]
      .ghostDirections[UP]
      .ghostFrames[0] =
      (SDL_Rect){520, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_PINKY]
      .ghostDirections[UP]
      .ghostFrames[1] =
      (SDL_Rect){536, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_PINKY]
      .ghostDirections[DOWN]
      .ghostFrames[0] =
      (SDL_Rect){552, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_PINKY]
      .ghostDirections[DOWN]
      .ghostFrames[1] =
      (SDL_Rect){568, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // INKY
  globalSpriteSheet->ghostNormal[GHOSTTYPE_INKY]
      .ghostDirections[RIGHT]
      .ghostFrames[0] =
      (SDL_Rect){456, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_INKY]
      .ghostDirections[RIGHT]
      .ghostFrames[1] =
      (SDL_Rect){472, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_INKY]
      .ghostDirections[LEFT]
      .ghostFrames[0] =
      (SDL_Rect){488, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_INKY]
      .ghostDirections[LEFT]
      .ghostFrames[1] =
      (SDL_Rect){504, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_INKY]
      .ghostDirections[UP]
      .ghostFrames[0] =
      (SDL_Rect){520, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_INKY]
      .ghostDirections[UP]
      .ghostFrames[1] =
      (SDL_Rect){536, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_INKY]
      .ghostDirections[DOWN]
      .ghostFrames[0] =
      (SDL_Rect){552, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_INKY]
      .ghostDirections[DOWN]
      .ghostFrames[1] =
      (SDL_Rect){568, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // CLYDE
  globalSpriteSheet->ghostNormal[GHOSTTYPE_CLYDE]
      .ghostDirections[RIGHT]
      .ghostFrames[0] =
      (SDL_Rect){456, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_CLYDE]
      .ghostDirections[RIGHT]
      .ghostFrames[1] =
      (SDL_Rect){472, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_CLYDE]
      .ghostDirections[LEFT]
      .ghostFrames[0] =
      (SDL_Rect){488, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_CLYDE]
      .ghostDirections[LEFT]
      .ghostFrames[1] =
      (SDL_Rect){504, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_CLYDE]
      .ghostDirections[UP]
      .ghostFrames[0] =
      (SDL_Rect){520, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_CLYDE]
      .ghostDirections[UP]
      .ghostFrames[1] =
      (SDL_Rect){536, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_CLYDE]
      .ghostDirections[DOWN]
      .ghostFrames[0] =
      (SDL_Rect){552, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[GHOSTTYPE_CLYDE]
      .ghostDirections[DOWN]
      .ghostFrames[1] =
      (SDL_Rect){568, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // Populate ZERO_DIRECTION fallbacks to prevent undefined behavior issues
  for (int i = 0; i < GHOST_COUNT; i++) {
    globalSpriteSheet->ghostNormal[i].ghostDirections[ZERO_DIRECTION] =
        globalSpriteSheet->ghostNormal[i].ghostDirections[RIGHT];
  }
  // Ghost Frightened
  globalSpriteSheet->ghostFrightened[0] =
      (SDL_Rect){584, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostFrightened[1] =
      (SDL_Rect){600, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // Ghost Flashing
  globalSpriteSheet->ghostFlashing[0] =
      (SDL_Rect){616, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostFlashing[1] =
      (SDL_Rect){632, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // Ghost Eyes
  globalSpriteSheet->ghostEyes[RIGHT] =
      (SDL_Rect){520, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostEyes[LEFT] =
      (SDL_Rect){536, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostEyes[UP] =
      (SDL_Rect){552, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostEyes[DOWN] =
      (SDL_Rect){568, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostEyes[ZERO_DIRECTION] =
      (SDL_Rect){520, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // Fruit
  globalSpriteSheet->cherry =
      (SDL_Rect){488, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->strawberry =
      (SDL_Rect){504, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->orange =
      (SDL_Rect){520, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->apple =
      (SDL_Rect){536, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->devilFruit =
      (SDL_Rect){552, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->scepter =
      (SDL_Rect){568, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->bell =
      (SDL_Rect){584, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->key =
      (SDL_Rect){600, 32, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // Score
  globalSpriteSheet->score100 =
      (SDL_Rect){456, 152, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score1000 =
      (SDL_Rect){520, 152, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score1600 =
      (SDL_Rect){504, 144, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score200 =
      (SDL_Rect){456, 144, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score2000 =
      (SDL_Rect){456, 160, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score300 =
      (SDL_Rect){472, 152, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score3000 =
      (SDL_Rect){472, 160, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score400 =
      (SDL_Rect){472, 144, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score500 =
      (SDL_Rect){488, 152, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score5000 =
      (SDL_Rect){488, 160, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score700 =
      (SDL_Rect){504, 152, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->score800 =
      (SDL_Rect){488, 144, GENERAL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  return true;
}
void GraphicsDrawTile(SDL_Renderer *renderer, MapTile tile, int x, int y) {
  SDL_Rect sourceRectangle;
  switch (tile) {
  case TILE_DOT: {
    sourceRectangle = globalSpriteSheet->dot;
    break;
  }
  case TILE_POWER_PELLET: {
    sourceRectangle = globalSpriteSheet->powerPellet;
    break;
  }
  case TILE_GHOST_DOOR: {
    sourceRectangle = globalSpriteSheet->ghostDoor;
    break;
  }
  default:
    return;
  }
  SDL_Rect destinationRectangle = {x, y, MAP_GRID_CELL_SIZE,
                                   MAP_GRID_CELL_SIZE};
  SDL_RenderCopy(renderer, globalSpriteSheet->texture, &sourceRectangle,
                 &destinationRectangle);
}
void GraphicsDrawEdible(SDL_Renderer *renderer, Entity edibleEntity) {
  if (globalSpriteSheet == NULL) {
    printf("[graphics.c] - GraphicsDrawEdible() globalSpriteSheet is NULL\n");
  }
  Edible *edibleComponent = ECS_GetEdible(edibleEntity);
  if (edibleComponent == NULL) {
    printf("[graphics.c] - Edible Component is NULL\n");
    return;
  }
  Position *ediblePosition = ECS_GetPosition(edibleEntity);
  if (ediblePosition == NULL) {
    printf("[graphics.c] - edible Position is NULL\n");
    return;
  }
  SDL_Rect destinationRectangle = {
      (int)((ediblePosition->column + ediblePosition->offsetX) *
            MAP_GRID_CELL_SIZE),
      (int)((ediblePosition->row + ediblePosition->offsetY) *
            MAP_GRID_CELL_SIZE),
      MAP_GRID_CELL_SIZE, MAP_GRID_CELL_SIZE};
  SDL_Rect sourceRectangle;
  switch (edibleComponent->typeEaten) {
  case DOT: {
    sourceRectangle = globalSpriteSheet->dot;
    break;
  }
  case POWER_PELLET: {
    sourceRectangle = globalSpriteSheet->powerPellet;
    break;
  }
  case FRUIT: {
    // If you want to draw a cherry or fruit as fallback
    sourceRectangle = globalSpriteSheet->cherry;
    break;
  }
  default: {
    return; // FRIGHTENED_GHOST or unhandled types won't use this logic
  }
  }
  SDL_RenderCopy(renderer, globalSpriteSheet->texture, &sourceRectangle,
                 &destinationRectangle);
}
void GraphicsDrawGhost(SDL_Renderer *renderer, Entity ghostEntity,
                       GameContext *gameContext) {
  if (globalSpriteSheet == NULL) {
    printf("[graphics.c] - globalSpriteSheet is NULL\n");
    return;
  }
  Ghost *ghostComponent = ECS_GetGhost(ghostEntity);
  if (ghostComponent == NULL) {
    printf("[graphics.c] - Ghost Component is NULL\n");
    return;
  }
  Position *ghostPosition = ECS_GetPosition(ghostEntity);
  if (ghostPosition == NULL) {
    printf("[graphics.c] - Ghost Position is NULL\n");
    return;
  }
  SDL_Rect destinationRectangle = {
      (int)((ghostPosition->column + ghostPosition->offsetX) *
            MAP_GRID_CELL_SIZE),
      (int)((ghostPosition->row + ghostPosition->offsetY) * MAP_GRID_CELL_SIZE),
      MAP_GRID_CELL_SIZE, MAP_GRID_CELL_SIZE};
  SDL_Rect sourceRectangle;
  int ghostIndex = (int)ghostComponent->ghostType;
  switch (ghostComponent->ghostMode) {
  case GHOSTMODE_EATEN_EYES: {
    Velocity *ghostVelocity = ECS_GetVelocity(ghostEntity);
    Direction eyeDirection = ZERO_DIRECTION;
    if (ghostVelocity != NULL) {
      if (ghostVelocity->deltaColumn > 0) {
        eyeDirection = RIGHT;
      } else if (ghostVelocity->deltaColumn < 0) {
        eyeDirection = LEFT;
      } else if (ghostVelocity->deltaRow < 0) {
        eyeDirection = UP;
      } else if (ghostVelocity->deltaRow > 0) {
        eyeDirection = DOWN;
      }
    }
    sourceRectangle = globalSpriteSheet->ghostEyes[eyeDirection];
    break;
  }
  case GHOSTMODE_FRIGHTENED: {
    float timer = gameContext->frightenedGhostModeTimer;
    bool isFlashing = (timer >= FRIGHTEN_GHOST_MODE_DURATION - 2.0f);
    if (isFlashing == true) {
      // Advance flash timer
      staticGhostFlashTimer += gameContext->deltaTime;
      if (staticGhostFlashTimer >= 1.0f / GHOST_FLASHING_SPEED) {
        staticGhostFlashTimer = 0.0f;
        // Move between element 0 and 1
        staticGhostFlashFrame = (staticGhostFlashFrame + 1) % 2;
      }
      sourceRectangle = globalSpriteSheet->ghostFlashing[staticGhostFlashFrame];
    } else {
      // Advance frightened timer
      staticGhostFrightTimer += gameContext->deltaTime;
      if (staticGhostFrightTimer >= 1.0f / 6.0f) {
        staticGhostFrightTimer = 0.0f;
        staticGhostFrightFrame = (staticGhostFrightFrame + 1) % 2;
      }
      sourceRectangle =
          globalSpriteSheet->ghostFrightened[staticGhostFrightFrame];
    }
    break;
  }
  default: {
    static int normalFrame = 0;
    static float normalTimer = 0.0f;
    normalTimer += gameContext->deltaTime;
    if (normalTimer >= 0.15f) {
      normalTimer = 0.0f;
      normalFrame = (normalFrame + 1) % 2;
    }
    Direction currentDirection = ghostComponent->currentDirection;
    if (currentDirection < 0 || currentDirection >= 5) {
      currentDirection = ZERO_DIRECTION;
    }
    sourceRectangle = globalSpriteSheet->ghostNormal[ghostIndex]
                          .ghostDirections[currentDirection]
                          .ghostFrames[normalFrame];
    break;
  }
  }
  SDL_RenderCopy(renderer, globalSpriteSheet->texture, &sourceRectangle,
                 &destinationRectangle);
}
void GraphicsDrawPlayer(SDL_Renderer *renderer, Entity playerEntity,
                        GameContext *gameContext) {
  if (globalSpriteSheet == NULL) {
    printf("[graphics.c] - GraphicsDrawPlayer() globalSpriteSheet is NULL\n");
  }
  Position *playerPosition = ECS_GetPosition(playerEntity);
  Velocity *playerVelocity = ECS_GetVelocity(playerEntity);
  SDL_Rect *animationFrames = NULL;
  // Point to the start of the array for each Pacman animation sets
  if (playerVelocity->deltaColumn > 0) {
    animationFrames = globalSpriteSheet->pacmanRight;
  } else if (playerVelocity->deltaColumn < 0) {
    animationFrames = globalSpriteSheet->pacmanLeft;
  } else if (playerVelocity->deltaRow > 0) {
    animationFrames = globalSpriteSheet->pacmanDown;
  } else if (playerVelocity->deltaRow < 0) {
    animationFrames = globalSpriteSheet->pacmanUp;
  } else {
    // Not moving fact right for now. TODO: Face the last direction
    animationFrames = globalSpriteSheet->pacmanRight;
  }
  staticPacmanAnimationTimer += gameContext->deltaTime;
  if (staticPacmanAnimationTimer >= (1.0f / PACMAN_ANIMATION_FPS)) {
    staticPacmanAnimationTimer = 0.0f;
    staticPacmanCurrentFrame =
        (staticPacmanCurrentFrame + 1) % PACMAN_ANIMATION_FRAMES;
  }
  SDL_Rect sourceRectangle = animationFrames[staticPacmanCurrentFrame];
  SDL_Rect destinationRectangle = {
      (int)((playerPosition->column + playerPosition->offsetX) *
            MAP_GRID_CELL_SIZE),
      (int)((playerPosition->row + playerPosition->offsetY) *
            MAP_GRID_CELL_SIZE),
      MAP_GRID_CELL_SIZE, MAP_GRID_CELL_SIZE};
  SDL_RenderCopy(renderer, globalSpriteSheet->texture, &sourceRectangle,
                 &destinationRectangle);
}

bool InitializeTTF() {
  if (TTF_Init() == -1) {
    return false;
  }
  globalFont = TTF_OpenFont(PUBLICPIXELTTF, 12);
  return true;
}
void ShutdownGraphics() {
  if (globalSpriteSheet != NULL) {
    if (globalSpriteSheet->texture != NULL) {
      SDL_DestroyTexture(globalSpriteSheet->texture);
      free(globalSpriteSheet);
      globalSpriteSheet = NULL;
    }
  }
}
void ShutdownTTF() {
  if (globalFont != NULL) {
    globalFont = NULL;
  }
  TTF_Quit();
}

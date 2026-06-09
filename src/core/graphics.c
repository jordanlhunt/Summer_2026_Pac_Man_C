#include "../../include/graphics.h"
#include <stdbool.h>

SpriteSheet *globalSpriteSheet = NULL;
TTF_Font *globalFont = NULL;

// PAC-MAN Animation State
static float staticPacmanAnimationTimer = 0.0f;
static int staticPacmanCurrentFrame;
// Ghost Animation State
static float staticGhostFlashTimer = 0.0f;
static int staticGhostFlashFrame = 0;
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
  if (globalSpriteSheet == NULL) {
    printf("[graphics.c] - Failed to create globalSpriteSheet textue: %s\n",
           SDL_GetError());
    return false;
  }
  /* --  Get all of the sprites from the sheet --  */
  // Maze Tiles
  globalSpriteSheet->dot =
      (SDL_Rect){0, 24, SMALL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->powerPellet =
      (SDL_Rect){8, 236, SMALL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
  globalSpriteSheet->ghostDoor = (SDL_Rect){0, 236, 16, 4};
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
  // Left Movement
  globalSpriteSheet->ghostNormal[BLINKY][0] =
      (SDL_Rect){456, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[BLINKY][1] =
      (SDL_Rect){472, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[PINKY][0] =
      (SDL_Rect){472, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[PINKY][1] =
      (SDL_Rect){456, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[INKY][0] =
      (SDL_Rect){456, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[INKY][1] =
      (SDL_Rect){472, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[CLYDE][0] =
      (SDL_Rect){456, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostNormal[CLYDE][1] =
      (SDL_Rect){472, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // Ghost Frightened
  globalSpriteSheet->ghostFrightened[0] =
      (SDL_Rect){456, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostFrightened[1] =
      (SDL_Rect){472, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // Ghost Flashing
  globalSpriteSheet->ghostFlashing[0] =
      (SDL_Rect){488, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostFlashing[1] =
      (SDL_Rect){504, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  // Ghost Eyes
  globalSpriteSheet->ghostEyes[0] =
      (SDL_Rect){520, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostEyes[1] =
      (SDL_Rect){536, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostEyes[2] =
      (SDL_Rect){552, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
  globalSpriteSheet->ghostEyes[3] =
      (SDL_Rect){568, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
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
}
void GraphicsDrawTile(SDL_Renderer *renderer, MapTile tile) {
  SDL_Rect sourceRectangle;
  switch (tile) {
  case TILE_DOT: {
    sourceRectangle = globalSpriteSheet->dot;
    break;
  }
  case TILE_POWER_PELLET: {
    sourceRectangle = globalSpriteSheet->powerPellet;
    break;
#include "../../include/graphics.h"
#include <stdbool.h>

    SpriteSheet *globalSpriteSheet = NULL;
    TTF_Font *globalFont = NULL;

    // PAC-MAN Animation State
    static float staticPacmanAnimationTimer = 0.0f;
    static int staticPacmanCurrentFrame;
    // Ghost Animation State
    static float staticGhostFlashTimer = 0.0f;
    static int staticGhostFlashFrame = 0;
    bool InitializeGraphics(SDL_Renderer * renderer,
                            const char *spriteSheetPath) {
      SDL_Surface *sourceSpriteSheetSurface = IMG_Load(spriteSheetPath);
      if (sourceSpriteSheetSurface == NULL) {
        printf("[graphics.c] - Failed to load sprite sheet: %s\n",
               IMG_GetError());
        return false;
      }
      // malloc spriteSheet
      globalSpriteSheet = malloc(sizeof(SpriteSheet));
      if (globalSpriteSheet == NULL) {
        SDL_FreeSurface(sourceSpriteSheetSurface);
        printf("[graphics.c] - Failed to malloc spritesheet");
        return false;
      }
      // Load the source sheet with all the textures
      globalSpriteSheet->texture =
          SDL_CreateTextureFromSurface(renderer, sourceSpriteSheetSurface);
      SDL_FreeSurface(sourceSpriteSheetSurface);
      if (globalSpriteSheet == NULL) {
        printf("[graphics.c] - Failed to create globalSpriteSheet textue: %s",
               SDL_GetError());
        return false;
      }
      /* --  Get all of the sprites from the sheet --  */
      // Maze Tiles
      globalSpriteSheet->dot =
          (SDL_Rect){0, 24, SMALL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
      globalSpriteSheet->powerPellet =
          (SDL_Rect){8, 236, SMALL_SPRITE_SIZE, SMALL_SPRITE_SIZE};
      globalSpriteSheet->ghostDoor = (SDL_Rect){0, 236, 16, 4};
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
      // Left Movement
      globalSpriteSheet->ghostNormal[BLINKY][0] =
          (SDL_Rect){456, 64, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostNormal[BLINKY][1] =
          (SDL_Rect){472, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostNormal[PINKY][0] =
          (SDL_Rect){472, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostNormal[PINKY][1] =
          (SDL_Rect){456, 80, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostNormal[INKY][0] =
          (SDL_Rect){456, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostNormal[INKY][1] =
          (SDL_Rect){472, 96, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostNormal[CLYDE][0] =
          (SDL_Rect){456, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostNormal[CLYDE][1] =
          (SDL_Rect){472, 112, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      // Ghost Frightened
      globalSpriteSheet->ghostFrightened[0] =
          (SDL_Rect){456, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostFrightened[1] =
          (SDL_Rect){472, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      // Ghost Flashing
      globalSpriteSheet->ghostFlashing[0] =
          (SDL_Rect){488, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostFlashing[1] =
          (SDL_Rect){504, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      // Ghost Eyes
      globalSpriteSheet->ghostEyes[0] =
          (SDL_Rect){520, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostEyes[1] =
          (SDL_Rect){536, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostEyes[2] =
          (SDL_Rect){552, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
      globalSpriteSheet->ghostEyes[3] =
          (SDL_Rect){568, 128, GENERAL_SPRITE_SIZE, GENERAL_SPRITE_SIZE};
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
    }
  }
  case TILE_GHOST_DOOR: {
    sourceRectangle = globalSpriteSheet->ghostDoor;
    break;
  }
  default:
    return;
  }
  SDL_RenderCopy(renderer, globalSpriteSheet->texture, &sourceRectangle, NULL);
}

void GraphicsDrawGhost(SDL_Renderer *renderer, Entity ghostEntity) {
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
    Velocity *ghostVelocity = ECS_GetVelocity(ghostVelocity);
    int eyeDirection = 0;
    if (ghostVelocity->deltaColumn > 0) {
      eyeDirection = RIGHT;
    } else if (ghostVelocity->deltaColumn < 0) {
      eyeDirection = LEFT;
    } else if (ghostVelocity->deltaRow < 0) {
      eyeDirection = UP;
    } else if (ghostVelocity->deltaRow > 0) {
      eyeDirection = DOWN;
    }
    sourceRectangle = globalSpriteSheet->ghostEyes[eyeDirection];
    break;
  }
  case GHOSTMODE_FRIGHTENED: {
    float timer =
        0.0f; /* FIXME: Get from gameContext->frigtenedghostModeTimer */
    bool isFlashing = (timer > 0.0f && timer < 2.0f);
    if (isFlashing == true) {
      gameContext->frightenedGhostModeTimer += deltaTime;
      if (staticGhostFlashTimer >= 1.0f / GHOST_FLASHING_SPEED) {
        staticGhostFlashTimer = 0.0f;
        staticGhostFlashFrame = !staticGhostFlashFrame;
      }
      sourceRectangle = globalSpriteSheet->ghostFlashing[staticGhostFlashFrame];
    } else {
      static int frightFrame = 0;
      frightFrame = (frightFrame + 1) % 2;
      sourceRectangle = globalSpriteSheet->ghostFrightened[frightFrame];
    }
    break;
  }
  default: {
    static int normalFrame = 0;
    static float normalTimer = 0.0f;
    normalFrame += deltaTime;
    if (normalTimer >= 0.1f) {
      normalTimer = 0.0f;
      normalFrame = (normalFrame + 1) % 2;
    }
    sourceRectangle = globalSpriteSheet->ghostNormal[ghostIndex][normalFrame];
    break;
  }
  }
  SDL_RenderCopy(renderer, globalSpriteSheet->texture, &sourceRectangle,
                 &destinationRectangle);
}
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

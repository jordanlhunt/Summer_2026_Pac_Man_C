#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "common.h"
#include "ecs/components.h"
#include "ecs/ecs.h"
#include "ecs/entity.h"
#include "gamecontext.h"
#include "maptile.h"
#define GENERAL_SPRITE_SIZE 16
#define SMALL_SPRITE_SIZE 8
#define PACMAN_ANIMATION_FRAMES 3
#define PACMAN_DEATH_ANIMATION_FRAMES 11
#define PACMAN_ANIMATION_FPS 12.0f
#define GHOST_ANIMATION_FRAMES 2
#define GHOST_FLASHING_SPEED 6.0f
#define GHOST_EYES 5

typedef struct SpriteAnimation2Frames {
  SDL_Rect ghostFrames[GHOST_ANIMATION_FRAMES];
} SpriteAnimation2Frames;

typedef struct SpriteGroupGhost {
  // Direction Enums is 5: ZERO_DIRECTION will default to RIGHT
  SpriteAnimation2Frames ghostDirections[GHOST_EYES];
}

typedef struct SpriteSheet {
  SDL_Texture *texture;
  SDL_Rect wall;
  SDL_Rect dot;
  SDL_Rect powerPellet;
  SDL_Rect ghostDoor;
  // PAC-MAN
  SDL_Rect pacmanRight[PACMAN_ANIMATION_FRAMES];
  SDL_Rect pacmanLeft[PACMAN_ANIMATION_FRAMES];
  SDL_Rect pacmanUp[PACMAN_ANIMATION_FRAMES];
  SDL_Rect pacmanDown[PACMAN_ANIMATION_FRAMES];
  SDL_Rect pacmanDeath[PACMAN_DEATH_ANIMATION_FRAMES];
  // Ghosts
  SDL_Rect ghostNormal[GHOST_COUNT][GHOST_DIRECTIONS][GHOST_ANIMATION_FRAMES];
  SDL_Rect ghostFrightened[GHOST_ANIMATION_FRAMES];
  SDL_Rect ghostFlashing[GHOST_ANIMATION_FRAMES];
  SDL_Rect ghostEyes[GHOST_EYES];
  // Fruits
  SDL_Rect cherry;
  SDL_Rect strawberry;
  SDL_Rect orange;
  SDL_Rect apple;
  SDL_Rect devilFruit;
  SDL_Rect scepter;
  SDL_Rect bell;
  SDL_Rect key;
  // Scores
  SDL_Rect score100;
  SDL_Rect score200;
  SDL_Rect score300;
  SDL_Rect score400;
  SDL_Rect score500;
  SDL_Rect score700;
  SDL_Rect score800;
  SDL_Rect score1000;
  SDL_Rect score1600;
  SDL_Rect score2000;
  SDL_Rect score3000;
  SDL_Rect score5000;
} SpriteSheet;
extern TTF_Font *globalFont;
extern SpriteSheet *globalSpriteSheet;
// pointer to GameContext for deltaTime

bool InitializeGraphics(SDL_Renderer *renderer, const char *spriteSheetPath);
bool InitializeTTF();
void ShutdownGraphics();
void ShutdownTTF();
void GraphicsDrawTile(SDL_Renderer *renderer, MapTile tile);
void GraphicsDrawGhost(SDL_Renderer *renderer, Entity ghostEntity,
                       GameContext *gameContext);
void GraphicsDrawPlayer(SDL_Renderer *renderer, Entity playerEntity,
                        GameContext *gameContext);
#endif

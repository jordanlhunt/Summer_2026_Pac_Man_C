#include "../../include/player.h"
// Initalize the player in the center of the screen for testing purposes the
// values for this will be changed in the future when I get the actual sprites.
void initializePlayer(GameContext* gameContext) {
  gameContext->player.x = 100;
  gameContext->player.y = 100;
  gameContext->player.velocity = 10;
  gameContext->player.width = 20;
  gameContext->player.height = 20;
}
// Update the player on GameContext->input
void updatePlayer(GameContext* gameContext) {
  if (gameContext->input.moveLeft) {
    gameContext->player.x -= gameContext->player.velocity;
  }
  if (gameContext->input.moveRight) {
    gameContext->player.x = gameContext->player.velocity;
  }
  if (gameContext->input.moveUp) {
    gameContext->player.y -= gameContext->player.velocity;
  }
  if (gameContext->input.moveDown) {
    gameContext->player.y = gameContext->player.velocity;
  }
  handleWindowBounds();
}
void drawPlayer(GameContext* gameContext, SDL_Renderer* renderer) {
  SDL_Rect playerRect = {(int)gameContext->player.x, (int)gameContext->player.y,
                         gameContext->player.width, gameContext->player.height};
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // YELLOW for now
  SDL_RenderFillRect(renderer, &playerRect);
}
void handleWindowBounds() {
  if (gameContext->player.x < 0) {
    gameContext->player.x = 0;
  }
  if (gameContext->player.y < 0) {
    gameContext->player.y = 0;
  }
  if (gameContext->player.x + gameContext->player.width > SCREEN_WIDTH) {
    gameContext->player.x = SCREEN_WIDTH - gameContext->player.width;
  }
  if (gameContext->player.y + gameContext->player.Height > SCREEN_HEIGHT) {
    gameContext->player.y = SCREEN_HEIGHT - gameContext->player.height;
  }
}
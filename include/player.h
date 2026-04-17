#ifndef PLAYER_H
#define PLAYER_H
// Forward Delecrations
typedef struct GameContext GameContext;
typedef struct SDL_Renderer SDL_Renderer;

void initializePlayer(GameContext* gameContext);
void updatePlayer(GameContext* gameContext);
void drawPlayer(GameContext* gameContext, SDL_Renderer* renderer);
#endif
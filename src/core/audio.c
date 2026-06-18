#include "../../include/audio.h"

static Mix_Chunk *staticWakaSound0 = NULL;
static Mix_Chunk *staticWakaSound1 = NULL;

Mix_Chunk LoadSound(char *soundFile) {
  Mix_Chunk *soundEffectChunk = Mix_LoadWAV(soundFile);
  if (soundEffectChunk == NULL) {
    printf("[audio.c] - Failed to load sound %s\n", soundFile);
  }
  return *soundEffectChunk;
}

void PlaySound(Mix_Chunk *soundEffect) { Mix_PlayChannel(-1, soundEffect, 0); }

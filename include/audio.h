#ifndef AUDIO_H
#define AUDIO_H
#include "common.h"
Mix_Chunk LoadSound(char *soundFile);
void PlaySound(Mix_Chunk *soundEffect);
#endif

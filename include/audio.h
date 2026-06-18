#ifndef AUDIO_H
#define AUDIO_H
#include "common.h"
typedef enum SoundEffectId {
  SOUNDEFFECT_WAKA0,
  SOUNDEFFECT_WAKA1,
  SOUNDEFFECT_POWER_PELLET,
  SOUNDEFFECT_GHOST_EATEN,
  SOUNDEFFECT_PLAYER_DEATH,
  SOUNDEFFECT_FRUIT,
  SOUNDEFFECT_COUNT
} SoundEffectId;
typedef struct AudioState {
  Mix_Chunk *soundEffects[SOUNDEFFECT_COUNT];
  Mix_Chunk *waka0;
  Mix_Chunk *waka1;
  int wakaSoundEffectToggle;
  Mix_Music *backgroundMusic;
} AudioState;
bool InitializeAudio(AudioState *audioState);
bool AudioLoadAssets(AudioState *audioState);
void AudioPlaySoundEffect(AudioState *audioState, SoundEffectId soundEffectId);
void AudioPlayWaka(AudioState *audioState);
void AudioPlayMusic(AudioState *audioState, bool isLooping);
void AudioResetWaka(AudioState *audioState);
void ShutdownAudio(AudioState *audioState);
#endif

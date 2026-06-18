#ifndef AUDIO_H
#define AUDIO_H
#include "common.h"
#define AUDIO_FREQENCY 44100
#define AUDIO_CHANNELS 2
#define AUDIO_CHUNK_SIZE 2048
#define AUDIO_SOUNDEFFECT_CHANNEL_COUNT 16
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

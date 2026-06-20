#include "../../include/audio.h"
#include <SDL2/SDL_mixer.h>
#include <time.h>
static const char *WAKA0_FILEPATH = "assets/audio/eat_dot_0.wav";
static const char *WAKA1_FILEPATH = "assets/audio/eat_dot_1.wav";
static const char *BACKGROUND_FILEPATH = "assets/audio/start.wav";
bool InitializeAudio(AudioState *audioState) {
  if (audioState == NULL) {
    return false;
  }
  memset(audioState, 0, sizeof(*audioState));
  if (Mix_OpenAudio(AUDIO_FREQENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS,
                    AUDIO_CHUNK_SIZE) < 0) {
    return false;
  }
  Mix_AllocateChannels(AUDIO_SOUNDEFFECT_CHANNEL_COUNT);
  audioState->wakaSoundEffectToggle = 0;
  if (AudioLoadAssets(audioState) == false) {
    return false;
  }
  return true;
}
bool AudioLoadAssets(AudioState *audioState) {
  audioState->waka0 = Mix_LoadWAV(WAKA0_FILEPATH);
  audioState->waka1 = Mix_LoadWAV(WAKA1_FILEPATH);
  audioState->startMusic = Mix_LoadMUS(BACKGROUND_FILEPATH);
  return true;
}
void AudioPlayMusic(AudioState *audioState, int isLooping) {
  if (audioState == NULL || audioState->backgroundMusic == NULL) {
    return;
  }
  Mix_PlayMusic(audioState->backgroundMusic, isLooping);
}
void AudioPlayWaka(AudioState *audioState) {
  if (audioState == NULL) {
    return;
  }
  Mix_Chunk *wakaSound = NULL;
  if (audioState->wakaSoundEffectToggle == 0) {
    wakaSound = audioState->waka0;
  } else {
    wakaSound = audioState->waka1;
  }
  audioState->wakaSoundEffectToggle = !(audioState->wakaSoundEffectToggle);
  if (wakaSound != NULL) {
    Mix_PlayChannel(-1, wakaSound, 0);
  }
}
void AudioPlayStartMusic(AudioState *audioState) {
  if (audioState == NULL || audioState->startMusic == NULL) {
    return;
  }
  Mix_PlayMusic(audioState->startMusic, AUDIO_DO_NOT_LOOP_MUSIC);
}
void AudioPlaySoundEffect(AudioState *audioState, SoundEffectId soundEffectId) {
  if (audioState == NULL) {
    return;
  }
  if (soundEffectId == SOUNDEFFECT_WAKA) {
    AudioPlayWaka(audioState);
    return;
  }
}
void ShutdownAudio(AudioState *audioState) {
  // Free all sound chunks and music first
  if (audioState != NULL) {
    if (audioState->waka0 != NULL) {
      Mix_FreeChunk(audioState->waka0);
      audioState->waka0 = NULL;
    }
    if (audioState->waka1 != NULL) {
      Mix_FreeChunk(audioState->waka1);
      audioState->waka1 = NULL;
    }
    for (int i = 0; i < SOUNDEFFECT_COUNT; i++) {
      if (audioState->soundEffects[i] != NULL) {
        Mix_FreeChunk(audioState->soundEffects[i]);
        audioState->soundEffects[i] = NULL;
      }
    }
    if (audioState->backgroundMusic != NULL) {
      Mix_FreeMusic(audioState->backgroundMusic);
      audioState->backgroundMusic = NULL;
    }
    if (audioState->startMusic != NULL) {
      Mix_FreeMusic(audioState->startMusic);
      audioState->startMusic = NULL;
    }
  }
  // Close mixer before SDL_Quit
  Mix_CloseAudio();
}

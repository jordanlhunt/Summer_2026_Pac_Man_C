#include "../../include/audio.h"

  static const char* WAKA0_FILEPATH = "assets/audio/eat_dot_0.wav";
  static const char* WAKA1_FILEPATH = "assets/audio/eat_dot_1.wav";


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
  return true;
}
bool AudioLoadAssets(AudioState *audioState) {

  audioState->waka0 = Mix_LoadWAV(WAKA0_FILEPATH);
  audioState->waka1 = Mix_LoadWAV(WAKA1_FILEPATH);
  // TODO: Do all the other sounds & Music
  return true;
}

void
  
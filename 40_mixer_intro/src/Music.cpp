#include "../include/Music.hpp"
#include <SDL2/SDL_mixer.h>
#include <iostream>

Music::Music(std::string musicFilePath) {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    std::cout << "MIX OPENAUDIO ERROR: " << Mix_GetError() << '\n';
  }
  // load our music file
  m_music = Mix_LoadMUS(musicFilePath.c_str());
}

Music::~Music() { Mix_FreeMusic(m_music); }

// number of times to play the music
// 0 mean 0
// 1 means play forever
void Music::playMusic(int loops) {
  if (m_music != nullptr)
    Mix_PlayMusic(m_music, loops);
}
void Music::stopMusic() { Mix_PauseMusic(); }
// A range 0 to 120
void Music::setVolume(int volume) { Mix_VolumeMusic(volume); }

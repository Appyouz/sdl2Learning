#include "../include/Sound.hpp"
#include <iostream>

Sound::Sound(std::string filepath) {

  if (SDL_LoadWAV(filepath.c_str(), &m_audioSpec, &m_waveStart,
                  &m_waveLength) == nullptr) {
    std::cerr << "sound loading error: " << SDL_GetError() << std::endl;
  }
}

Sound::~Sound() {
  SDL_FreeWAV(m_waveStart);
  SDL_CloseAudioDevice(m_device);
}

void Sound::playSound() {
  int status{SDL_QueueAudio(m_device, m_waveStart, m_waveLength)};
  // the 0 indicates false which means no pause, just play
  SDL_PauseAudioDevice(m_device, 0);
}

void Sound::stopSound() { SDL_PauseAudioDevice(m_device, 0); }

void Sound::setupDevice() {
  m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr,
                                 SDL_AUDIO_ALLOW_ANY_CHANGE);
  if (m_device == 0) {
    std::cerr << "Sound device error: " << SDL_GetError() << '\n';
  }
}

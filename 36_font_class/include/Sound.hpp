#ifndef SOUND_HPP
#define SOUND_HPP

#include <SDL2/SDL.h>
#include <string>

// interface for audio
class ISound {
public:
  // Virtual destructor for our interface
  virtual ~ISound(){};

  // Member functions that needs to be implemented
  virtual void playSound() = 0;
  virtual void stopSound() = 0;
};

class Sound : public ISound {
private:
  // Device that sound will play on
  // headphone, speaker, soundcard, etc.
  SDL_AudioDeviceID m_device;

  // Properties of wave file that is loaded
  // i.e. sound data
  SDL_AudioSpec m_audioSpec;
  Uint8 *m_waveStart;
  Uint32 m_waveLength;

public:
  Sound(std::string filepath);
  ~Sound();

  void playSound();
  void stopSound();
  // specific to SDL api
  void setupDevice();
};
#endif

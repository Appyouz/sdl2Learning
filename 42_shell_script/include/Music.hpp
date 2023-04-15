#ifndef MUSIC_HPP
#define MUSIC_HPP
#include <SDL2/SDL_mixer.h>
#include <string>
class Music {
private:
  Mix_Music* m_music;
public:
  Music(std::string musicFilePath);
  ~Music();

  void playMusic(int loops);
  void stopMusic();
  void setVolume(int volume);
};
#endif

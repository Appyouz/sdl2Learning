#ifndef TEXT_HPP
#define TEXT_HPP


// sdl2 ttf font library for drawing text
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
class Text {
private:
  static bool m_ttfInitialized;
public:
  Text();
  ~Text();

  void drawText();
  
};
#endif

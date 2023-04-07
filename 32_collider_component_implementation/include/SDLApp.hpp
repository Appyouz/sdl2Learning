#ifndef SDL_APP_H
#define SDL_APP_H
#include <SDL2/SDL.h>
#include <functional>
#include <iostream>

class SDLApp {
private:
  SDL_Window *m_window{nullptr};
  SDL_Renderer *m_renderer{nullptr};
  bool m_gameIsRunning{true};
  // variables to store mouse positions
  int m_mouseX{};
  int m_mouseY{};

  // set frame cap
  int m_maxFrameRate{};
  // store width and height of a window
  int m_width{};
  int m_height{};

  // store our call back function
  std::function<void(void)> m_eventCallBack;
  std::function<void(void)> m_updateCallBack;
  std::function<void(void)> m_renderCallBack;

public:
  SDLApp(const char *title, int x, int y, int w, int h);

  ~SDLApp();

  void SetEventCallBack(std::function<void(void)> func);
  
  void SetUpdateCallBack(std::function<void(void)> func);

  void SetRenderCallBack(std::function<void(void)> func);
  void RunLoop();

  // set maximum render rate for each frame( frame cap)
  void setMaxFrameRate(int frameRate);

  SDL_Renderer *GetRenderer() const;

  int GetMouseX();
  int GetMouseY();


  //return window dimension
  int getWindowWidth();
  int getWindowHeight();

  void StopAppLoop();
};

#endif // !SDL_APP_H

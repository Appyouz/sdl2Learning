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

  // store our call back function
  std::function<void(void)> m_eventCallBack;
  std::function<void(void)> m_renderCallBack;

public:
  SDLApp(const char *title, int x, int y, int w, int h);

  ~SDLApp();

  void SetEventCallBack(std::function<void(void)> func);

  void SetRenderCallBack(std::function<void(void)> func);
  void RunLoop();

  SDL_Renderer *GetRenderer() const;

  int GetMouseX();
  int GetMouseY();

  void StopAppLoop();
};

#endif // !SDL_APP_H

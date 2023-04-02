#include "../include/SDLApp.hpp"
#include <iostream>

SDLApp::SDLApp(const char *title, int x, int y, int w, int h) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not be initialized: " << SDL_GetError() << '\n';
  } else {
    std::cout << "SDL video system is ready to go." << '\n';
  }

  m_window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

SDLApp::~SDLApp() {
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void SDLApp::SetEventCallBack(std::function<void(void)> func) {
  m_eventCallBack = func;
}

void SDLApp::SetRenderCallBack(std::function<void(void)> func) {
  m_renderCallBack = func;
}
void SDLApp::RunLoop() {

  while (m_gameIsRunning) {

    Uint32 buttons{SDL_GetMouseState(&m_mouseX, &m_mouseY)};
    // handle event first
    m_eventCallBack();

    SDL_SetRenderDrawColor(GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(GetRenderer());

    SDL_SetRenderDrawColor(GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);

    // then handle rendering
    m_renderCallBack();

    SDL_RenderPresent(GetRenderer());

    // Eventually set a frame cap
    SDL_Delay(100);
  }
}

SDL_Renderer *SDLApp::GetRenderer() const { return m_renderer; }

int SDLApp::GetMouseX() { return m_mouseX; }
int SDLApp::GetMouseY() { return m_mouseY; }

void SDLApp::StopAppLoop() { m_gameIsRunning = false; }

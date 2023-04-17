#include "../include/SDLApp.hpp"
#include <SDL2/SDL_timer.h>
#include <iostream>

SDLApp::SDLApp(Uint32 subSystemFlags,const char *title, int x, int y, int w, int h) {

  m_width = w;
  m_height = h;

  //default cap value
  m_maxFrameRate = 60;

  // Return the window dimension

  if (SDL_Init(subSystemFlags) < 0) {
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

void SDLApp::SetUpdateCallBack(std::function<void ()> func){
  m_updateCallBack = func;
}

void SDLApp::SetRenderCallBack(std::function<void(void)> func) {
  m_renderCallBack = func;
}
void SDLApp::RunLoop() {

  while (m_gameIsRunning) {
    Uint32 startTime {SDL_GetTicks()};

    Uint32 buttons{SDL_GetMouseState(&m_mouseX, &m_mouseY)};
    //1. handle event first
    m_eventCallBack();

    // 2. handle updates
    m_updateCallBack();
    SDL_SetRenderDrawColor(GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(GetRenderer());

    SDL_SetRenderDrawColor(GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);

    //3. then handle rendering
    m_renderCallBack();

    SDL_RenderPresent(GetRenderer());

    Uint32 elapsedTime {SDL_GetTicks() - startTime};
    if(elapsedTime < m_maxFrameRate){
    // Eventually set a frame cap
      SDL_Delay( m_maxFrameRate - elapsedTime);
    }
  }
}

void SDLApp::setMaxFrameRate(int frameRate){
  m_maxFrameRate = frameRate;
}
SDL_Renderer *SDLApp::GetRenderer() const { return m_renderer; }

int SDLApp::GetMouseX() { return m_mouseX; }
int SDLApp::GetMouseY() { return m_mouseY; }

int SDLApp::getWindowWidth() { return m_width; }
int SDLApp::getWindowHeight() { return m_height; }

void SDLApp::StopAppLoop() { m_gameIsRunning = false; }

 SDL_TimerID SDLApp::addTimer(Uint32 delay, SDL_TimerCallback callback, void *param){
  SDL_TimerID id {SDL_AddTimer(delay, callback, param)};
  m_timers.insert(id);
  return id;
}

SDL_TimerID SDLApp::addrecurringTimer(Uint32 interval, SDL_TimerCallback callback, void *param){
  SDL_TimerID id {SDL_AddTimer(interval, callback, param)};
  m_timers.insert(id);
  SDL_Event event ;
  SDL_UserEvent userevent;
  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  userevent.data1 = NULL;
  userevent.data2 = NULL;

  event.type = SDL_USEREVENT;
  event.user = userevent;
  SDL_PushEvent(&event);
  return(interval);
}
void SDLApp::removeTimer(SDL_TimerID id){
  if(SDL_RemoveTimer(id) == SDL_FALSE){
    std::cout << "Error, time not removed.\n";
  }else {
    m_timers.erase(id);
  }
}

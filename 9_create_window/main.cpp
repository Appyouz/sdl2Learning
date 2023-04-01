#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>

#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  SDL_Window * window {nullptr};

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not be initialized: " << SDL_GetError() << '\n'; 
  }else {
    std::cout << "SDL video system is ready to go." << '\n';
  }

  window = SDL_CreateWindow("first window", 0, 0, 640, 480, SDL_WINDOW_SHOWN);
  SDL_Delay(3000);

  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}

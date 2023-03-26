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


  // game loop event
   bool gameIsRunning {true};

  while (gameIsRunning)
  {
    SDL_Event event;
    
    //start event loop
    while (SDL_PollEvent(&event))
    {
      //handle each specific event
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) 
          gameIsRunning = false;

      if (event.type == SDL_MOUSEMOTION) 
        std::cout << "Mouse has been moved!\n";

      if (event.type == SDL_KEYDOWN) 
        std::cout << "A key has been pressed\n";
    }
    
  }

  SDL_Delay(3000);

  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}

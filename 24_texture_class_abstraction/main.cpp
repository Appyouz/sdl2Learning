#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "TextureRectangle.hpp"

int main (int argc, char *argv[])
{
	SDL_Window* window {nullptr};

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not be initialized: " << SDL_GetError() << '\n'; 
  }else {
    std::cout << "SDL video system is ready to go." << '\n';
  }

  window = SDL_CreateWindow(
      "first window", 
      20, 
      20,
      640,
      480,
      SDL_WINDOW_SHOWN);

		SDL_Renderer* renderer {nullptr};
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		
		TextureRectangle rect {renderer, "./images/3D-Window_BBB_Blender_2.bmp"};

  bool gameIsRunning {true};

  while (gameIsRunning)
  {
    SDL_Event event;
    
    while (SDL_PollEvent(&event))
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
            gameIsRunning = false;
            std::cout << "Escaped key pressed\n";
        }
    }

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			rect.setRectangleProperties(20, 30, 200, 200);
			rect.render(renderer);
      SDL_RenderPresent(renderer);
  }


  SDL_DestroyWindow(window);

  SDL_Quit();


	return 0;
}

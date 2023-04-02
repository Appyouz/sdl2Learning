#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "../include/TextureRectangle.hpp"
#include "../include/AnimatedSprite.hpp"


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
		
		AnimatedSprite animatedSprite{renderer, "./images/edited.bmp"};
		animatedSprite.Draw(200, 200, 150, 150);

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
			
			static int frameNumber {0};
			animatedSprite.PlayFrame(0, 0, 170, 110, frameNumber);
			animatedSprite.Render(renderer);
			frameNumber++;
			if(frameNumber > 6)
				frameNumber = 0;


      SDL_RenderPresent(renderer);
			SDL_Delay(100);
  }


  SDL_DestroyWindow(window);

  SDL_Quit();


	return 0;
}

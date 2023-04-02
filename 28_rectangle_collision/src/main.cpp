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
		
    TextureRectangle object1{renderer, "./images/test.bmp"};
    TextureRectangle object2{renderer, "./images/test.bmp"};
		
		bool gameIsRunning {true};

  while (gameIsRunning)
  {
    SDL_Event event;

     //variables to store mouse positions
      int mouseX {};
      int mouseY {};
      Uint32 buttons {SDL_GetMouseState(&mouseX, &mouseY)};

    while (SDL_PollEvent(&event))
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
            gameIsRunning = false;
            std::cout << "Escaped key pressed\n";
        }
        
        if (event.button.button == SDL_BUTTON_LEFT) {
          if(object2.isColliding(object1))
            std::cout << "Is Colliding.\n";
          else 
            std::cout << "Is Not Colliding.\n";
        }
    }

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

      // Draw positions and size
      object1.Draw(50, 50, 100, 100);
      object2.Draw(mouseX, mouseY, 100, 100);
			
      object1.render(renderer);
      object2.render(renderer);


      SDL_RenderPresent(renderer);
			SDL_Delay(100);
  }


  SDL_DestroyWindow(window);

  SDL_Quit();


	return 0;
}

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[])
{
  SDL_Window * window {nullptr};


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

  SDL_Renderer* renderer {nullptr} ;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  
  bool gameIsRunning {true};

	// setup and initialize sdl2 image library with supported format
	int flags { IMG_INIT_PNG};
	int initStatus {IMG_Init(flags)};
	if((initStatus & flags) != flags ){
		std::cout << "SDL2 image format not available.\n";
	}

	SDL_Surface* image {nullptr};
	image = IMG_Load("./images/mario.png");

	if (!image) {
		std::cout << "Failed to load image...\n";
	}

	SDL_Texture* ourPNG { nullptr};
	ourPNG = SDL_CreateTextureFromSurface(renderer, image);

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

      SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, ourPNG, NULL, NULL);

      SDL_RenderPresent(renderer);
  }


  SDL_DestroyWindow(window);

	SDL_FreeSurface(image);
	SDL_DestroyTexture(ourPNG);
	IMG_Quit();
  SDL_Quit();

	return 0;
}

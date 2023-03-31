#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


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

   if (TTF_Init() == -1) {
		std::cout << "Could not initialize SDL_ttf. Error: " << TTF_GetError()	<< '\n';
   }else {
		std::cout << "SDL_ttf working...\n"<<'\n';
	}

	// load our font file and set the font size
	TTF_Font* ourFont = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf", 32);
	
	// confirm it was loaded
	if(ourFont == nullptr){
		std::cout << "Could not load font.\n"; 
		std::exit(1);
	}

	//pixels from our text
  SDL_Surface* surfaceText = TTF_RenderText_Solid(ourFont, "SDL2 learning series", {255, 255, 255});

	
  SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
  SDL_FreeSurface(surfaceText);
    


  SDL_Rect rectangle;
  rectangle.x  = 10;
  rectangle.y  = 10;
  rectangle.w  = 400;
  rectangle.h  = 100;

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

      SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, textureText, NULL, &rectangle);
      SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(textureText);

  SDL_DestroyWindow(window);

	TTF_CloseFont(ourFont);
  SDL_Quit();



  return 0;
}

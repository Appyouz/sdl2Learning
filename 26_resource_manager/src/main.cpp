#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include "../include/TextureRectangle.hpp"


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
		

		std::vector<std::shared_ptr<TextureRectangle>> rects;
    for(int i=0; i < 10; i++){
        std::shared_ptr<TextureRectangle> rect = std::make_shared<TextureRectangle>(renderer,"./images/3D-Window_BBB_Blender_2.bmp");
        rects.push_back(rect);
    }

    int row = 0;
    int col = 1;
    for(int i=0; i < 10; i++){
        rects[i]->setRectangleProperties(100*col,30*row,200,200);
        if(i%3==0){
            row++;
            col=1;
        }
        col++;
    }
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

        for(auto& rect: rects){
            rect->render(renderer);
        }

      SDL_RenderPresent(renderer);
  }


  SDL_DestroyWindow(window);

  SDL_Quit();


	return 0;
}

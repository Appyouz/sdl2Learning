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

  window = SDL_CreateWindow(
      "first window", 
      0, 
      0,
      640,
      480,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  SDL_Renderer* renderer {nullptr} ;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Surface* surface = SDL_LoadBMP("./images/3D-Window_BBB_Blender_2.bmp");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
    


  SDL_Rect rectangle;
  rectangle.x  = 50;
  rectangle.y  = 100;
  rectangle.w  = 200;
  rectangle.h  = 200;


  // game loop event
   bool gameIsRunning {true};

  // main application loop
  while (gameIsRunning)
  {
    SDL_Event event;
    
    //start event loop
    while (SDL_PollEvent(&event))
    {
      // 1. Handle event input
      const Uint8* state = SDL_GetKeyboardState(NULL);
      if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
          gameIsRunning = false;
          std::cout << "Escaped key pressed\n";
      }
    }
     // 2. Handle updates

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Do drawing here
    // draws white line nice
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 5, 5, 100, 120);

    // draw rectangle


    SDL_RenderDrawRect(renderer, &rectangle);
      // renderer, texture, source, destination
    SDL_RenderCopy(renderer, texture, NULL, &rectangle );



    // Finally show what we have drawn
    SDL_RenderPresent(renderer);


    
  }

  SDL_DestroyTexture(texture);

  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}

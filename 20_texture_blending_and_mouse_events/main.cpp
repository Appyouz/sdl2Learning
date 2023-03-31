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
      20, 
      20,
      640,
      480,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  SDL_Renderer* renderer {nullptr} ;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Surface* surface = SDL_LoadBMP("./images/kong.bmp");

  // set the color key after  loading the surface, and before the texture
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface -> format, 0xFF, 0, 0xFF));

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
    


  SDL_Rect rectangle;
  rectangle.x  = 50;
  rectangle.y  = 100;
  rectangle.w  = 200;
  rectangle.h  = 200;

  SDL_Rect rectangle2;
  rectangle2.x  = 50;
  rectangle2.y  = 100;
  rectangle2.w  = 200;
  rectangle2.h  = 200;



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

      if(event.type == SDL_MOUSEMOTION)
      {
        rectangle2.x = event.motion.x;
        rectangle2.x = event.motion.y;

      }

      if(event.type == SDL_MOUSEBUTTONDOWN)
      {
        if(event.button.button == SDL_BUTTON_LEFT)
        {
          SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
        }else if(event.button.button == SDL_BUTTON_MIDDLE)
        {
          SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        }else if(event.button.button == SDL_BUTTON_RIGHT)
        {
          SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MOD);
        }

        }else {
          SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);

      }
    }
     // 2. Handle updates

    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Do drawing here
    // draws white line nice
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 5, 5, 200, 220);

    // draw rectangle
    // SDL_RenderDrawRect(renderer, &rectangle);
    
      // renderer, texture, source, destination
    // copying texture into gpu i guess
    SDL_RenderCopy(renderer, texture, NULL, &rectangle );
    SDL_RenderCopy(renderer, texture, NULL, &rectangle2 );



    // Finally show what we have drawn
    SDL_RenderPresent(renderer);


    
  }

  SDL_DestroyTexture(texture);

  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}

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
      SDL_WINDOW_SHOWN);

  SDL_Renderer* renderer {nullptr} ;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Surface* surface = SDL_LoadBMP("./images/pool2.bmp");

  // set the color key after  loading the surface, and before the texture
  // SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface -> format, 0xFF, 0, 0xFF));

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
    


  SDL_Rect rectangle;
  rectangle.x  = 0;
  rectangle.y  = 0;
  rectangle.w  = 640;
  rectangle.h  = 480;

  SDL_Rect rectangle2;
  rectangle2.x  = -639;
  rectangle2.y  = 0;
  rectangle2.w  = 640;
  rectangle2.h  = 480;

  SDL_Rect rectangle3;
  rectangle3.x  = 0;
  rectangle3.y  = 0;
  rectangle3.w  = 640;
  rectangle3.h  = 480;

  SDL_Rect rectangle4;
  rectangle4.x  = 0;
  rectangle4.y  = -480;
  rectangle4.w  = 640;
  rectangle4.h  = 480;

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

        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
          if(event.button.button == SDL_BUTTON_LEFT){
            SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_ADD);
            std::cout << "Left mouse button pressed.\n";
          }else if(event.button.button == SDL_BUTTON_MIDDLE){
            SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND);
            std::cout << "Middle mouse button pressed.\n";
          }else if(event.button.button == SDL_BUTTON_RIGHT)
          {
            SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_MOD);
            std::cout << "Right mouse button pressed.\n";
          }
        }
    }

      SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

        int w{};
        int h{};
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        SDL_Delay(25);


        // handle textures scrolling left to right
        rectangle.x++;
        if (rectangle.x > 639)
          rectangle.x = -639;

        rectangle2.x++;
        if(rectangle2.x > 639)
          rectangle2.x = -639;

        rectangle3.y++;
        if(rectangle3.y > 479)
          rectangle3.y = -480;
   
        rectangle4.y++;
        if(rectangle3.y > 479)
          rectangle3.y = -480;  

        // order matters, scrolling left and right
      SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
      SDL_RenderCopy(renderer, texture, NULL, &rectangle );
      SDL_RenderCopy(renderer, texture, NULL, &rectangle2 );
      
      // scrolling up and down
      SDL_RenderCopy(renderer, texture, NULL, &rectangle3 );
      SDL_RenderCopy(renderer, texture, NULL, &rectangle4 );

      SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);

  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}

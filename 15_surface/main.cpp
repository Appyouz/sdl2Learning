#include <SDL2/SDL_video.h>
#include <iostream>

#include <SDL2/SDL.h>


int main(int argc, char* argv[])
{
  // Create a window data type
  SDL_Window * window {nullptr};

  // grab the  window  surface
  SDL_Surface* screen;

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

     screen = SDL_GetWindowSurface(window);

     SDL_Surface* image;
     image = SDL_LoadBMP("./images/3D-Window_BBB_Blender_2.bmp");
  // blit or copy to the screen/window 
     SDL_BlitSurface(image, NULL, screen, NULL);
     SDL_FreeSurface(image);

     SDL_UpdateWindowSurface(window);


  // game loop event
   bool gameIsRunning {true};

  while (gameIsRunning)
  {
    SDL_Event event;
    
    //start event loop
    while (SDL_PollEvent(&event))
    {

      const Uint8* state = SDL_GetKeyboardState(NULL);
      //handle each specific event
      if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
          gameIsRunning = false;
          std::cout << "Escaped key pressed\n";
      }

      if (event.type == SDL_MOUSEMOTION) 
        std::cout << "Mouse has been moved!\n";

      if (event.type == SDL_KEYDOWN) 
        std::cout << "A key has been pressed\n";

      if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) 
        std::cout << "Right and up keys were pressed\n";
      
    }


    
  }

  SDL_Delay(3000);

  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}

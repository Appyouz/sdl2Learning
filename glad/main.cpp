#include <iostream>

#include <SDL2/SDL.h>

#include <glad/glad.h>

int main(int argc, char* argv[])
{
  SDL_Window * window {nullptr};

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not be initialized: " << SDL_GetError() << '\n'; 
  }else {
    std::cout << "SDL video system is ready to go." << '\n';
  }

  // Before we create our window, need to specify OpenGL version
  // check SDL_GL_SetAttribute

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // 1 here is true for doublebuffer (meaning it updates twice 
  // as often and has 24 bits of color)
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  
  window = SDL_CreateWindow(
      "first window", 
      0, 
      0,
      640,
      480,
      SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    // OpenGL setup graphics context
    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);

  // Setup our function pointers
  gladLoadGLLoader(SDL_GL_GetProcAddress);

  // game loop event
   bool gameIsRunning {true};

  while (gameIsRunning)
  {
    glViewport(0, 0, 640, 480);
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

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // SDL_GL_SwapWindow needs an addres as parameters
    // since window is already a pointer no need to pass with '&'
    SDL_GL_SwapWindow(window);
    
  }

  SDL_Delay(3000);

  SDL_DestroyWindow(window);
  SDL_Quit();



  return 0;
}

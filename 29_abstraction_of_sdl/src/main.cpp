#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../include/AnimatedSprite.hpp"
#include "../include/SDLApp.hpp"
#include "../include/TextureRectangle.hpp"

SDLApp *app;

// Eventually  we will want some sort of factory
// to manage object creation
TextureRectangle *object1;
TextureRectangle *object2;
void handleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
      app->StopAppLoop();
      std::cout << "Escaped key pressed\n";
    }

    if (event.button.button == SDL_BUTTON_LEFT) {
      if (object2->isColliding(*object1))
        std::cout << "Is Colliding.\n";
      else
        std::cout << "Is Not Colliding.\n";
    }
  }
}
void handleRendering() {
  // Draw positions and size
  object1->Draw(50, 50, 100, 100);
  object2->Draw(app->GetMouseX(), app->GetMouseY(), 100, 100);

  object1->render(app->GetRenderer());
  object2->render(app->GetRenderer());
}
int main(int argc, char *argv[]) {

  const char *title{"SDL learnging abstraction"};
  // setup SDLApp
  app = new SDLApp{title, 20, 20, 640, 480};

  object1 = new TextureRectangle{app->GetRenderer(), "./images/test.bmp"};
  object2 = new TextureRectangle{app->GetRenderer(), "./images/test.bmp"};

  // set callback()
  app->SetEventCallBack(handleEvents);
  app->SetRenderCallBack(handleRendering);
  app->RunLoop();
  delete app;
  delete object1;
  delete object2;
  return 0;
}

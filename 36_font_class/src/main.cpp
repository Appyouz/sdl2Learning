#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../include/AnimatedSprite.hpp"
#include "../include/DynamicText.hpp"
#include "../include/GameEntity.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/SDLApp.hpp"
#include "../include/Sound.hpp"
#include "../include/TextureRectangle.hpp"
#include "../include/Vector2d.hpp"

SDLApp *app;

// Eventually  we will want some sort of factory
// to manage object creation
GameEntity *object1;
GameEntity *object2;

Sound *CollisionSound;
void handleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
      app->StopAppLoop();
      std::cout << "Escaped key pressed\n";
    }
    //
    if (event.button.button == SDL_BUTTON_LEFT) {
      if (object2->getBoxCollider2d(0).isColliding(
              object1->getBoxCollider2d(0))) {
        std::cout << "Is Colliding with hit box 1.\n";
        CollisionSound->playSound();
      } else {
        std::cout << "Not Colliding with hit box 1.\n";
      }

      if (object2->getBoxCollider2d(0).isColliding(
              object1->getBoxCollider2d(1))) {
        std::cout << "Is Colliding with hit box 2.\n";
        CollisionSound->playSound();
      } else {
        std::cout << "Not Colliding with hit box 2.\n";
      }
    }
  }
}

void handleUpdate() {
  object1->update();
  object2->update();
  static int posX = 0;
  static int posY = 0;
  static bool up = true;
  static bool right = true;

  if (up) {
    posY--;
  } else {
    posY++;
  }

  if (right) {
    posX++;
  } else {
    posX--;
  }

  if (posX > app->getWindowWidth()) {
    right = false;
  } else if (posX < 0) {
    right = true;
  }

  if (posY < 0) {
    up = false;
  } else if (posY > app->getWindowHeight()) {
    up = true;
  }

  object2->setPosition(posX, posY);
  object2->setDimensions(100, 100);
  object1->setPosition(app->GetMouseX(), app->GetMouseY());
  object1->setDimensions(300, 300);

  object1->getBoxCollider2d(1).setDimensions(
      object1->getTexturedRectangle().getWidth(),
      object1->getTexturedRectangle().getHeight() / 2);

  Vector2d dims = object1->getBoxCollider2d(0).setBoundingBoxAutomatically(
      ResourceManager::GetInstance().GetSurface("./images/kong.bmp"), 0xFF,
      0x00, 0xFF);

  int newXPos = dims.x + app->GetMouseX();
  int newYPos = dims.y + app->GetMouseY();

  object1->getBoxCollider2d(0).setAbsolutePosition(newXPos, newYPos);
}
void handleRendering() {

  // Render our objects
  object1->render();
  object2->render();
  // Render the text after drawing the objects
  DynamicText text1("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 32);
  DynamicText text2("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 16);
  DynamicText text3("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 16);
  text1.DrawText(app->GetRenderer(), "Mike SDL2 Series", 0, 0, 100, 50);
  text2.DrawText(app->GetRenderer(), "Test!", 300, 300, 200, 50);

  static int counter = 0;
  counter++;
  text3.DrawText(app->GetRenderer(), std::to_string(counter), 50, 300, 50, 50);
}
int main(int argc, char *argv[]) {

  const char *title{"SDL learnging abstraction"};
  // setup SDLApp
  app = new SDLApp{SDL_INIT_VIDEO | SDL_INIT_AUDIO, title, 20, 20, 640, 480};
  // frame cap in terms of milliseconds
  // i.e 16mms = 60 frames
  app->setMaxFrameRate(16);

  object1 = new GameEntity{app->GetRenderer()};
  object1->addTexturedRectangleComponent("./images/kong.bmp", 0xFF, 0x00, 0xFF);
  object1->addBoxCollider2d();
  object1->addBoxCollider2d();

  object2 = new GameEntity{app->GetRenderer()};
  object2->addTexturedRectangleComponent("./images/kong.bmp");
  object2->addBoxCollider2d();

  // setup sounds
  CollisionSound = new Sound{"../assets/sounds/score.wav"};
  CollisionSound->setupDevice();

  // set callback()
  app->SetEventCallBack(handleEvents);
  app->SetUpdateCallBack(handleUpdate);
  app->SetRenderCallBack(handleRendering);
  app->RunLoop();
  delete app;
  delete object1;
  delete object2;
  delete CollisionSound;
  return 0;
}

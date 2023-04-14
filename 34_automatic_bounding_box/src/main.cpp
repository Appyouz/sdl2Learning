#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../include/AnimatedSprite.hpp"
#include "../include/GameEntity.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/SDLApp.hpp"
#include "../include/TextureRectangle.hpp"
#include "../include/Vector2d.hpp"

SDLApp *app;

// Eventually  we will want some sort of factory
// to manage object creation
GameEntity *object1;
GameEntity *object2;
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
      } else {
        std::cout << "Not Colliding with hit box 1.\n";
      }

      if (object2->getBoxCollider2d(0).isColliding(
              object1->getBoxCollider2d(1))) {
        std::cout << "Is Colliding with hit box 2.\n";
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

  /*
      object1->getCollider2d(0).setAbsolutePosition(
          object1->getTextureRectangle().getPositionX(),
          object1->getTextureRectangle().getPositionY());
      object1->getCollider2d(0).setDimensions(
          object1->getTextureRectangle().getWidth(),
          object1->getTextureRectangle().getHeight() / 2);

      object1->getCollider2d(1).setAbsolutePosition(
          object1->getTextureRectangle().getPositionX(),
          object1->getTextureRectangle().getPositionY() +
              object1->getTextureRectangle().getHeight() / 2);
      object1->getCollider2d(1).setDimensions(
          object1->getTextureRectangle().getWidth(),
          object1->getTextureRectangle().getHeight() / 2);

      object2->getCollider2d(0).setAbsolutePosition(
          object2->getTextureRectangle().getPositionX(),
          object2->getTextureRectangle().getPositionY());
      object2->getCollider2d(0).setDimensions(
          object2->getTextureRectangle().getWidth(),
          object2->getTextureRectangle().getHeight()); */

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
}
int main(int argc, char *argv[]) {

  const char *title{"SDL learnging abstraction"};
  // setup SDLApp
  app = new SDLApp{title, 20, 20, 640, 480};
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

  // set callback()
  app->SetEventCallBack(handleEvents);
  app->SetUpdateCallBack(handleUpdate);
  app->SetRenderCallBack(handleRendering);
  app->RunLoop();
  delete app;
  delete object1;
  delete object2;
  return 0;
}

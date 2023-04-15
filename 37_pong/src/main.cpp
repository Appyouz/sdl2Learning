#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <cstdio>
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
GameEntity *leftPaddle;
GameEntity *rightPaddle;
GameEntity *ball;

Sound *CollisionSound;
Sound *ScoreSound;

struct GameState {
  float movementSpeed;
  float ballSpeed;
  int ballXDirection;
  int ballYDirection;
  int leftScore;
  int rightScore;
};

GameState *gameState;

void handleEvents() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
      app->StopAppLoop();
      std::cout << "Escaped key pressed\n";
    }

    if (event.type == SDL_KEYDOWN) {
      // any time key is pressed lets retrieve
      // the positions of our paddle (X,Y)
      int leftPaddleX = leftPaddle->getTexturedRectangle().getPositionX();
      int leftPaddleY = leftPaddle->getTexturedRectangle().getPositionY();

      int rightPaddleX = rightPaddle->getTexturedRectangle().getPositionX();
      int rightPaddleY = rightPaddle->getTexturedRectangle().getPositionY();

      if (event.key.keysym.sym == SDLK_UP) {
        rightPaddleY -= gameState->movementSpeed;
        rightPaddle->setPosition(rightPaddleX, rightPaddleY);

      } else if (event.key.keysym.sym == SDLK_DOWN) {

        rightPaddleY += gameState->movementSpeed;
        rightPaddle->setPosition(rightPaddleX, rightPaddleY);

      } else if (event.key.keysym.sym == SDLK_w) {

        leftPaddleY -= gameState->movementSpeed;
        leftPaddle->setPosition(leftPaddleX, leftPaddleY);

      } else if (event.key.keysym.sym == SDLK_s) {

        leftPaddleY += gameState->movementSpeed;
        leftPaddle->setPosition(leftPaddleX, leftPaddleY);
      }
    }
  }
}

void handleUpdate() {
  // grabbing the ball position, and then
  // update it based on the direction ball is travelling

  int ballXposition = ball->getTexturedRectangle().getPositionX();
  int ballYposition = ball->getTexturedRectangle().getPositionY();
  // Detection of collision within a paddle
    if (ballXposition > 20 && leftPaddle->getBoxCollider2d(0).isColliding(
            ball->getBoxCollider2d(0))) {
      gameState->ballXDirection *= -1;
      CollisionSound->playSound();
      // detect where the collision happened
      int paddleMidPoint =
          leftPaddle->getTexturedRectangle().getPositionY() + 100;
      if (paddleMidPoint <= ballYposition) {
        gameState->ballYDirection = 1;

      } else if (paddleMidPoint > ballYposition) {

        gameState->ballYDirection = -1;
      }
    }

    if (ballXposition <= 610 && rightPaddle->getBoxCollider2d(0).isColliding(
            ball->getBoxCollider2d(0))) {
      gameState->ballXDirection *= -1;
      CollisionSound->playSound();
      int paddleMidPoint =
          rightPaddle->getTexturedRectangle().getPositionY() + 100;
      if (paddleMidPoint <= ballYposition) {
        gameState->ballYDirection = 1;

      } else if (paddleMidPoint > ballYposition) {

        gameState->ballYDirection = -1;
      }
    }

  // set ball boundary
  if (ballXposition > app->getWindowWidth() + 100) {

    ScoreSound->playSound();
    gameState->ballXDirection *= -1;
    gameState->leftScore++;
    // TODO: don't use number 10 use actual ball dimensions
    ballXposition = app->getWindowWidth() / 2 - 10;
    ballYposition = app->getWindowHeight() / 2 - 10;
  }

  // ball boundary
  if (ballXposition < -80) {

    ScoreSound->playSound();
    gameState->ballXDirection *= -1;
    gameState->rightScore++;
    ballXposition = app->getWindowWidth() / 2 - 10;
    ballYposition = app->getWindowHeight() / 2 - 10;
  }

  if (ballYposition > app->getWindowHeight()) {
    gameState->ballYDirection *= -1;
  }
  if (ballYposition < 0) {
    gameState->ballYDirection *= -1;
  }

  if (gameState->ballXDirection > 0) {
    ballXposition += gameState->movementSpeed;
  } else {

    ballXposition -= gameState->movementSpeed;
  }
  if (gameState->ballYDirection > 0) {

    ballYposition += gameState->movementSpeed;
  } else {

    ballYposition -= gameState->movementSpeed;
  }
  ball->setPosition(ballXposition, ballYposition);

  // hack to stop sounds
  static int currentTime = SDL_GetTicks();
  static int lastTime = SDL_GetTicks();
  currentTime = SDL_GetTicks();
  if (currentTime > lastTime + 1000) {
    ScoreSound->stopSound();
    CollisionSound->stopSound();
    lastTime = currentTime;
  }
}
void handleRendering() {

  // Render our objects
  leftPaddle->render();
  rightPaddle->render();
  ball->render();

  // Render the text after drawing the objects
  DynamicText leftScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 32);
  DynamicText rightScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 32);
  std::string lScore{"left: " + std::to_string(gameState->leftScore)};
  std::string rScore{"right: " + std::to_string(gameState->rightScore)};

  leftScore.DrawText(app->GetRenderer(), lScore, 0, 0, 100, 50);
  rightScore.DrawText(app->GetRenderer(), rScore, 500, 0, 100, 50);
}
int main(int argc, char *argv[]) {

  const char *title{"SDL2 PING PONG"};
  app = new SDLApp{SDL_INIT_VIDEO | SDL_INIT_AUDIO, title, 20, 20, 640, 480};
  app->setMaxFrameRate(16);

  leftPaddle = new GameEntity{app->GetRenderer()};
  leftPaddle->addTexturedRectangleComponent("./assets/images/leftpaddle.bmp");

  leftPaddle->getTexturedRectangle().setDimension(20, 200);
  leftPaddle->addBoxCollider2d();

  // //set our collider dimensions for left paddle
  leftPaddle->getBoxCollider2d(0).setDimensions(
      leftPaddle->getTexturedRectangle().getWidth(),
      leftPaddle->getTexturedRectangle().getHeight());

  leftPaddle->setPosition(10, 200);

  rightPaddle = new GameEntity{app->GetRenderer()};
  rightPaddle->addTexturedRectangleComponent("./assets/images/rightpaddle.bmp");
  rightPaddle->getTexturedRectangle().setDimension(20, 200);
  rightPaddle->addBoxCollider2d();
  // set our collider dimensions for rightpaddle
  rightPaddle->getBoxCollider2d(0).setDimensions(
      rightPaddle->getTexturedRectangle().getWidth(),
      rightPaddle->getTexturedRectangle().getHeight());
  rightPaddle->setPosition(610, 200);

  ball = new GameEntity{app->GetRenderer()};
  ball->addTexturedRectangleComponent("./assets/images/ball.bmp");
  ball->getTexturedRectangle().setDimension(20, 20);
  ball->addBoxCollider2d();

  // set our collider dimensions for ball
  ball->getBoxCollider2d(0).setDimensions(
      ball->getTexturedRectangle().getWidth(),
      ball->getTexturedRectangle().getHeight());

  ball->setPosition(app->getWindowWidth() / 2, app->getWindowHeight() / 2);

  // setup sounds
  CollisionSound = new Sound{"./assets/sounds/collide.wav"};
  CollisionSound->setupDevice();

  ScoreSound = new Sound{"./assets/sounds/score.wav"};
  ScoreSound->setupDevice();

  // setup gameState
  gameState = new GameState;
  gameState->movementSpeed = 5.0f;
  gameState->ballSpeed = 2.0f;
  gameState->ballXDirection = 1;
  gameState->ballYDirection = 1;
  gameState->leftScore = 0;
  gameState->rightScore = 0;

  // set callback()
  app->SetEventCallBack(handleEvents);
  app->SetUpdateCallBack(handleUpdate);
  app->SetRenderCallBack(handleRendering);

  app->RunLoop();

  // cleaning up the application
  delete app;
  delete leftPaddle;
  delete rightPaddle;
  delete ball;
  delete CollisionSound;
  delete ScoreSound;
  delete gameState;
  return 0;
}

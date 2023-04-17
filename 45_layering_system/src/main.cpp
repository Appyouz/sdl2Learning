#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../include/AnimatedSprite.hpp"
#include "../include/DynamicText.hpp"
#include "../include/EntityManager.hpp"
#include "../include/GameEntity.hpp"
#include "../include/Layer.hpp"
#include "../include/Music.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/SDLApp.hpp"
#include "../include/Sound.hpp"
#include "../include/TextureRectangle.hpp"
#include "../include/Vector2d.hpp"
SDLApp *app;

Sound *CollisionSound;
Sound *ScoreSound;

Music *MainMusicTrack;

struct GameState {
  float movementSpeed;
  float ballSpeed;
  int ballXDirection;
  int ballYDirection;
  int leftScore;
  int rightScore;
};

GameState *gameState;

// Handle the left paddle movement
void handleLeftPaddle() {
  std::shared_ptr<GameEntity> leftpaddle =
      EntityManager::GetInstance().GetEntityRef("leftpaddle");

  if (nullptr != leftpaddle) {
    int leftpaddlex = leftpaddle->getTexturedRectangle().getPositionX();
    int leftpaddley = leftpaddle->getTexturedRectangle().getPositionY();

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W]) {
      leftpaddley -= gameState->movementSpeed;
      leftpaddle->setPosition(leftpaddlex, leftpaddley);
    } else if (state[SDL_SCANCODE_S]) {
      leftpaddley += gameState->movementSpeed;
      leftpaddle->setPosition(leftpaddlex, leftpaddley);
    }
  }
}

// Handle the right paddle movement
void handleRightPaddle() {
  std::shared_ptr<GameEntity> rightpaddle =
      EntityManager::GetInstance().GetEntityRef("rightpaddle");

  if (nullptr != rightpaddle) {
    int rightpaddlex = rightpaddle->getTexturedRectangle().getPositionX();
    int rightpaddley = rightpaddle->getTexturedRectangle().getPositionY();

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP]) {
      rightpaddley -= gameState->movementSpeed;
      rightpaddle->setPosition(rightpaddlex, rightpaddley);
    } else if (state[SDL_SCANCODE_DOWN]) {
      rightpaddley += gameState->movementSpeed;
      rightpaddle->setPosition(rightpaddlex, rightpaddley);
    }
  }
}

// Callback function for handling events
void handleEvents() {
  SDL_Event event;

  // (1) Handle Input
  // Start our event loop
  while (SDL_PollEvent(&event)) {
    // Handle each specific event
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE]) {
      app->StopAppLoop();
      std::cout << "Escaped key pressed\n";
    }
  }
  // Handle paddle movement
  handleLeftPaddle();
  handleRightPaddle();
}

// Position the ball in the center of the court
void setBallPositionCenter() {
  std::shared_ptr<GameEntity> ball =
      EntityManager::GetInstance().GetEntityRef("ball");

  if (nullptr != ball) {
    int ballXposition = app->getWindowWidth() / 2 -
                        (ball->getTexturedRectangle().getWidth() / 2);
    int ballYposition = app->getWindowHeight() / 2 -
                        (ball->getTexturedRectangle().getHeight() / 2);

    // Set the ball position
    ball->setPosition(ballXposition, ballYposition);
  }
}

// Handle paddle collision
void handlePaddleCollision() {
  // Grabbing the ball position, and then
  // we will update it based on the direction the ball is traveling
  // Retrieve the created instance
  std::shared_ptr<GameEntity> leftpaddle =
      EntityManager::GetInstance().GetEntityRef("leftpaddle");
  std::shared_ptr<GameEntity> rightpaddle =
      EntityManager::GetInstance().GetEntityRef("rightpaddle");
  std::shared_ptr<GameEntity> ball =
      EntityManager::GetInstance().GetEntityRef("ball");
  int ballXposition = ball->getTexturedRectangle().getPositionX();
  int ballYposition = ball->getTexturedRectangle().getPositionY();

  // Detection of collision within a paddle
  if (ballXposition >= 20 && gameState->ballXDirection == -1 &&
      leftpaddle->getBoxCollider2d(0).isColliding(ball->getBoxCollider2d(0))) {
    gameState->ballXDirection = 1;
    CollisionSound->playSound();
    // Detect where the collision happened
    int paddleMidPoint =
        leftpaddle->getTexturedRectangle().getPositionY() + 100;
    if (paddleMidPoint <= ballYposition) {
      gameState->ballYDirection = -1;
    } else if (paddleMidPoint > ballYposition) {
      gameState->ballYDirection = 1;
    }
  } else if (ballXposition <= 610 && gameState->ballXDirection == 1 &&
             rightpaddle->getBoxCollider2d(0).isColliding(
                 ball->getBoxCollider2d(0))) {
    gameState->ballXDirection = -1;
    CollisionSound->playSound();
    // Detect where the collision happened
    int paddleMidPoint =
        rightpaddle->getTexturedRectangle().getPositionY() + 100;
    if (paddleMidPoint <= ballYposition) {
      gameState->ballYDirection = -1;
    } else if (paddleMidPoint > ballYposition) {
      gameState->ballYDirection = 1;
    }
  }

  // Set the ball position
  ball->setPosition(ballXposition, ballYposition);
}

// Handle boundaries along x and y axis of the game board
void handleBoundariesAndScoring() {
  // Grabbing the ball position, and then
  // we will update it based on the direction the ball is traveling
  std::shared_ptr<GameEntity> ball =
      EntityManager::GetInstance().GetEntityRef("ball");
  int ballXposition = ball->getTexturedRectangle().getPositionX();
  int ballYposition = ball->getTexturedRectangle().getPositionY();

  // Set ball boundaries (so we don't fly off the playing field)
  if (ballYposition > app->getWindowHeight()) {
    gameState->ballYDirection = -1;
  } else if (ballYposition < 0) {
    gameState->ballYDirection = 1;
  }
  // Set the ball position
  ball->setPosition(ballXposition, ballYposition);

  // Handle the case of scoring
  // The ball will be centered back to the screen if
  // a score takes place
  if (ballXposition > app->getWindowWidth() + 80) {
    ScoreSound->playSound();
    gameState->ballXDirection = -1;
    gameState->leftScore += 1;
    // Recenter ball to start
    setBallPositionCenter();
  } else if (ballXposition < -100) {
    ScoreSound->playSound();
    gameState->ballXDirection = 1;
    gameState->rightScore += 1;
    // Recenter ball to start
    setBallPositionCenter();
  }
}

// Handle the ball moving and it's direction
void handleBallMoving() {
  // Grabbing the ball position, and then
  // we will update it based on the direction the ball is traveling
  std::shared_ptr<GameEntity> ball =
      EntityManager::GetInstance().GetEntityRef("ball");
  int ballXposition = ball->getTexturedRectangle().getPositionX();
  int ballYposition = ball->getTexturedRectangle().getPositionY();
  // Move the ball left-to-right
  if (gameState->ballXDirection == 1) {
    ballXposition += gameState->movementSpeed;
  } else {
    ballXposition -= gameState->movementSpeed;
  }
  // Move the ball up-and-down
  if (gameState->ballYDirection == 1) {
    ballYposition += gameState->movementSpeed;
  } else {
    ballYposition -= gameState->movementSpeed;
  }

  // Set the ball position
  ball->setPosition(ballXposition, ballYposition);
}

// Update callback
void handleUpdate() {
  // Update all of our objects
  EntityManager::GetInstance().UpdateAll();
  // Grabbing the ball position, and then
  // we will update it based on the direction the ball is traveling
  std::shared_ptr<GameEntity> ball =
      EntityManager::GetInstance().GetEntityRef("ball");
  int ballXposition = ball->getTexturedRectangle().getPositionX();
  int ballYposition = ball->getTexturedRectangle().getPositionY();
  // Handle Ball Moving
  handleBallMoving();
  // Handle Boundaries and scoring
  handleBoundariesAndScoring();
  // Handle Collision with paddles
  handlePaddleCollision();

  // A bit of a hack, but we want to eventually stop
  // our sounds after some duration.
  static int currentTime = SDL_GetTicks();
  static int lastTime = SDL_GetTicks();
  currentTime = SDL_GetTicks();
  if (currentTime > lastTime + 1000) {
    ScoreSound->stopSound();
    CollisionSound->stopSound();
    lastTime = currentTime;
  }
}

// Handle the rendering of the game entities
void handleRendering() {
  // Render all of our objects
  EntityManager::GetInstance().RenderAllLayers();

  // Render the text after drawing the objects
  DynamicText leftScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 32);
  DynamicText rightScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 32);

  std::string lScore = "left: " + std::to_string(gameState->leftScore);
  std::string rScore = "right: " + std::to_string(gameState->rightScore);

  leftScore.DrawText(app->GetRenderer(), lScore, 0, 0, 100, 50);
  rightScore.DrawText(app->GetRenderer(), rScore, 500, 0, 100, 50);
}

Uint32 my_callbackfunc(Uint32 interval, void *param) {
  std::cout << "Fun score updated from: " << (const char *)param << ": "
            << gameState->leftScore << " - " << gameState->rightScore << '\n';
  return 0;
}

int main(int argc, char *argv[]) {
  // Setup the SDLApp
  const char *title = "SDL2 Series - Pong";
  app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER, title, 20,
                   20, 640, 480);
  app->setMaxFrameRate(16);

  // Create entities
  EntityManager::GetInstance().CreateEntity("court", app->GetRenderer(),
                                            Layer::background);
  EntityManager::GetInstance().CreateEntity("leftpaddle", app->GetRenderer(),
                                            Layer::foreground);
  EntityManager::GetInstance().CreateEntity("rightpaddle", app->GetRenderer(),
                                            Layer::foreground);
  EntityManager::GetInstance().CreateEntity("ball", app->GetRenderer(),
                                            Layer::foreground);

  // Retrieve the created instance
  std::shared_ptr<GameEntity> leftpaddle =
      EntityManager::GetInstance().GetEntityRef("leftpaddle");
  std::shared_ptr<GameEntity> rightpaddle =
      EntityManager::GetInstance().GetEntityRef("rightpaddle");
  std::shared_ptr<GameEntity> ball =
      EntityManager::GetInstance().GetEntityRef("ball");
  std::shared_ptr<GameEntity> court =
      EntityManager::GetInstance().GetEntityRef("court");

  // Create any objects in our scene
  leftpaddle->addTexturedRectangleComponent("./assets/images/leftpaddle.bmp");
  leftpaddle->getTexturedRectangle().setDimension(20, 200);
  leftpaddle->addBoxCollider2d();
  leftpaddle->getBoxCollider2d(0).setDimensions(
      leftpaddle->getTexturedRectangle().getWidth(),
      leftpaddle->getTexturedRectangle().getHeight());
  leftpaddle->setPosition(10, 200);

  rightpaddle->addTexturedRectangleComponent("./assets/images/rightpaddle.bmp");
  rightpaddle->getTexturedRectangle().setDimension(20, 200);
  rightpaddle->addBoxCollider2d();
  rightpaddle->getBoxCollider2d(0).setDimensions(
      rightpaddle->getTexturedRectangle().getWidth(),
      rightpaddle->getTexturedRectangle().getHeight());
  rightpaddle->setPosition(610, 200);

  ball->addTexturedRectangleComponent("./assets/images/ball.bmp");
  ball->addBoxCollider2d();
  ball->getTexturedRectangle().setDimension(20, 20);
  ball->getBoxCollider2d(0).setDimensions(
      ball->getTexturedRectangle().getWidth(),
      ball->getTexturedRectangle().getHeight());
  ball->setPosition(app->getWindowWidth() / 2, app->getWindowHeight() / 2);

  court->addTexturedRectangleComponent("./assets/images/court.bmp");
  court->getTexturedRectangle().setDimension(app->getWindowWidth(),
                                             app->getWindowHeight());
  court->setPosition(0, 0);

  // Setup our sounds
  CollisionSound = new Sound("./assets/sounds/collide.wav");
  // TODO: For now, we setup the device 'per sound'
  //       'may' make sense if we have several devices, or
  //       'capture' devices, likely we'll want to refactor
  //       this however.
  CollisionSound->setupDevice();

  // Setupt the score sound
  ScoreSound = new Sound("./assets/sounds/score.wav");
  ScoreSound->setupDevice();
  // Setup the music for our game
  MainMusicTrack = new Music("./assets/musics/guitarchords.mp3");
  MainMusicTrack->playMusic(-1);

  // Setup the Game State
  gameState = new GameState;
  gameState->movementSpeed = 5.0f;
  gameState->ballSpeed = 2.0f;
  gameState->ballXDirection = 1;
  gameState->ballYDirection = 1;
  gameState->leftScore = 0;
  gameState->rightScore = 0;

  // Set callback functions
  app->SetEventCallBack(handleEvents);
  app->SetUpdateCallBack(handleUpdate);
  app->SetRenderCallBack(handleRendering);

  // Add some timers (for demonstration purpose)
  app->addTimer(2000, my_callbackfunc, (char *)"timer called");
  // Run our application until terminated
  app->RunLoop();

  // Clean up our application
  delete app;
  delete CollisionSound;
  delete ScoreSound;
  // Clean up from our entity manager
  EntityManager::GetInstance().DeleteAllEntities();

  return 0;
}

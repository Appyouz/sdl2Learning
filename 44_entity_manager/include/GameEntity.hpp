#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include "Collider2d.hpp"
#include "TextureRectangle.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class GameEntity {
private:
  std::string m_name;
  TextureRectangle*  m_sprite;
  std::vector<BoxCollider2d*> m_colliders;

  // Pointer to the renderer that object will render
  // components to.
  SDL_Renderer *m_renderer;

public:
  // Constructors
  GameEntity();
  GameEntity(std::string name, SDL_Renderer *renderer);
  // Destructors
  ~GameEntity();
  // Update (called every loop)
  void update();
  // Render our Game Entity (In the render portion)
  void render();
  // Adding Rectangle Components
  void addTexturedRectangleComponent(std::string spritepath);
  // Adding a Rectangle component with transparency
  void addTexturedRectangleComponent(std::string spritepath, int redcolorkey,
                                     int greencolorkey, int bluecolorkey);
  // Add another Box Collider to our object
  void addBoxCollider2d();
  // Retrieve Components
  TextureRectangle &getTexturedRectangle();
  BoxCollider2d &getBoxCollider2d(size_t index);
  // Update
  // Note: Sets the position of our game entity
  //       This operates by moving all of the
  //       Components position as well so they are
  //       updated.
  void setPosition(int x, int y);
  // Sets all of the components to a specified dimension
  void setDimensions(int w, int h);
};

#endif // !GAME_ENTITY_HPP

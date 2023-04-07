#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP
#include "Collider2d.hpp"
#include "TextureRectangle.hpp"
#include <vector>

class Collider2d;
class GameEntity {
private:
  TextureRectangle *m_sprite;
  std::vector<Collider2d *> m_colliders;
  SDL_Renderer *m_renderer;

public:
  GameEntity();
  GameEntity(SDL_Renderer *renderer);
  ~GameEntity();

  void update();
  void render();

  // Adding components
  void addTexturedRectangleComponent(std::string spritePath);
  void addTexturedRectangleComponent(std::string spritePath, int redColorKey,
                                     int greenColorKey, int blueColorKey);

  void addCollider2d();
  // retrieve components
  TextureRectangle &getTextureRectangle();

  Collider2d &getCollider2d(size_t index);
};

#endif // !GAME_ENTITY_HPP

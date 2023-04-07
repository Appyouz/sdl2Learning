#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP
#include "TextureRectangle.hpp"
#include "Collider2d.hpp"

class Collider2d;
class GameEntity {
private:
  TextureRectangle *m_sprite;
  Collider2d *m_collider;
  SDL_Renderer *m_renderer;

public:
  GameEntity();
  GameEntity(SDL_Renderer *renderer, std::string spritePath);
  ~GameEntity();

  void update();
  void render();
  TextureRectangle &getTextureRectangle();
  Collider2d& getCollider2d();
};

#endif // !GAME_ENTITY_HPP

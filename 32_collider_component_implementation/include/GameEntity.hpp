#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP
#include "TextureRectangle.hpp"


class GameEntity {
private:
  TextureRectangle* m_sprite;
  SDL_Renderer* m_renderer;
public:
  GameEntity();
  GameEntity(SDL_Renderer* renderer, std::string spritePath);
  ~GameEntity();

  void update();
  void render();
  TextureRectangle& getTextureRectangle();
};

#endif // !GAME_ENTITY_HPP

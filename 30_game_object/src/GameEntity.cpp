#include "../include/GameEntity.hpp"

GameEntity::GameEntity(){
  m_sprite = nullptr;
}

GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritePath){
  m_renderer = renderer;
  m_sprite = new TextureRectangle {m_renderer, spritePath};
}

GameEntity::~GameEntity(){}

void GameEntity::update(){}
void GameEntity::render(){
  if (m_sprite != nullptr) {
    m_sprite->render(m_renderer);
  }
}


  TextureRectangle& GameEntity::getTextureRectangle(){
  return *m_sprite;
}

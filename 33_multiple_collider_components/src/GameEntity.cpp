#include "../include/GameEntity.hpp"
#include <SDL2/SDL_render.h>

GameEntity::GameEntity() { m_sprite = nullptr; }
GameEntity::GameEntity(SDL_Renderer *renderer) {
  m_sprite = nullptr;
  m_renderer = renderer;
}
void GameEntity::addTexturedRectangleComponent(std::string spritePath,
                                               int redColorKey,
                                               int greenColorKey,
                                               int blueColorKey) {
  m_sprite = new TextureRectangle{m_renderer, spritePath, redColorKey,
                                  greenColorKey, blueColorKey};
}

void GameEntity::addCollider2d() { m_colliders.push_back(new Collider2d{}); }
void GameEntity::addTexturedRectangleComponent(std::string spritePath) {
  m_sprite = new TextureRectangle{m_renderer, spritePath};
}
GameEntity::~GameEntity() {
  if (m_sprite != nullptr) {
    delete m_sprite;
  }

  for (int i{0}; i < m_colliders.size(); i++) {

    delete m_colliders[i];
  }
}

void GameEntity::update() {
  // update the position of our collider to be
  // the same as position of our sprite
  /* if (m_sprite != nullptr) {
    int x = m_sprite->getPositionX();
    int y = m_sprite->getPositionY();
    int w = m_sprite->getWidth();
    int h = m_sprite->getHeight();
  } */
}
void GameEntity::render() {
  if (m_sprite != nullptr) {
    m_sprite->render(m_renderer);
  }

  for (int i{0}; i < m_colliders.size(); i++) {
    if (m_colliders[i] != nullptr) {
      SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawRect(m_renderer, &m_colliders[i]->getColliderBoundingBox());
    }
  }
}

TextureRectangle &GameEntity::getTextureRectangle() { return *m_sprite; }

Collider2d &GameEntity::getCollider2d(size_t index) { return *m_colliders[index]; }

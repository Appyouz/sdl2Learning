#include "../include/GameEntity.hpp"
#include <SDL2/SDL_render.h>

GameEntity::GameEntity() { m_sprite = nullptr; }

GameEntity::GameEntity(SDL_Renderer *renderer, std::string spritePath) {
  m_renderer = renderer;
  m_sprite = new TextureRectangle{m_renderer, spritePath};
  m_collider = new Collider2d();
}

GameEntity::~GameEntity() {
  if (m_sprite != nullptr) {
    delete m_sprite;
  }

  if (m_collider != nullptr) {
    delete m_collider;
  }
}

void GameEntity::update() {
  // update the position of our collider to be
  // the same as position of our sprite
  if (m_sprite != nullptr) {
    int x = m_sprite->getPositionX();
    int y = m_sprite->getPositionY();
    int w = m_sprite->getWidth();
    int h = m_sprite->getHeight();

    if (m_collider != nullptr) {
      m_collider->setAbsolutePosition(x, y);
      m_collider->setDimensions(w, h);
    }
  }
}
void GameEntity::render() {
  if (m_sprite != nullptr) {
    m_sprite->render(m_renderer);
  }

  if (m_collider != nullptr) {
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(m_renderer, &m_collider->getColliderBoundingBox());
  }
}

TextureRectangle &GameEntity::getTextureRectangle() { return *m_sprite; }

Collider2d &GameEntity::getCollider2d() { return *m_collider; }

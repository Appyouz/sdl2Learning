#include "../include/GameEntity.hpp"
#include "../include/Collider2d.hpp"

GameEntity::GameEntity() {
  m_name = "unnamed";
  m_sprite = nullptr;
}
GameEntity::GameEntity(std::string name, SDL_Renderer *renderer) {
  m_name = name;
  m_sprite = nullptr;
  m_renderer = renderer;
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

void GameEntity::addBoxCollider2d() {
  m_colliders.push_back(new BoxCollider2d{});
}

void GameEntity::addTexturedRectangleComponent(std::string spritepath) {
  m_sprite = new TextureRectangle(m_renderer, spritepath);
}

void GameEntity::addTexturedRectangleComponent(std::string spritepath,
                                               int redcolorkey,
                                               int greencolorkey,
                                               int bluecolorkey) {
  m_sprite = new TextureRectangle(m_renderer, spritepath, redcolorkey,
                                  greencolorkey, bluecolorkey);
}

TextureRectangle &GameEntity::getTexturedRectangle() { return *m_sprite; }

BoxCollider2d &GameEntity::getBoxCollider2d(size_t index) {
  return *m_colliders[index];
}

void GameEntity::setPosition(int x, int y) {
  // Set the texture position
  if (nullptr != m_sprite) {
    m_sprite->setPosition(x, y);
  }
  for (int i = 0; i < m_colliders.size(); i++) {
    if (nullptr != m_colliders[i]) {
      m_colliders[i]->setAbsolutePosition(x, y);
    }
  }
}

void GameEntity::setDimensions(int w, int h) {
  // Set the texture position
  if (nullptr != m_sprite) {
    m_sprite->setDimension(w, h);
  }
  for (int i = 0; i < m_colliders.size(); i++) {
    if (nullptr != m_colliders[i]) {
      m_colliders[i]->setDimensions(w, h);
    }
  }
}

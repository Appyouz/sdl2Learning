#include "../include/Collider2d.hpp"

Collider2d::Collider2d() {
  m_colliderRectangle.x = 0;
  m_colliderRectangle.y = 0;
  m_colliderRectangle.w = 0;
  m_colliderRectangle.h = 0;
}
Collider2d::~Collider2d() {}
SDL_bool Collider2d::isColliding(Collider2d &collider) {
  const SDL_Rect temp{collider.m_colliderRectangle};
  return SDL_HasIntersection(&m_colliderRectangle, &temp);
}

SDL_Rect &Collider2d::getColliderBoundingBox() { return m_colliderRectangle; }

void Collider2d::setAbsolutePosition(int x, int y) {
  m_colliderRectangle.x = x;
  m_colliderRectangle.y = y;
}
void Collider2d::setDimensions(int w, int h) {
  m_colliderRectangle.w = w;
  m_colliderRectangle.h = h;
}

void Collider2d::update() {}
void Collider2d::render() {}

#ifndef COLLIDER_2D_HPP
#define COLLIDER_2D_HPP
#include <SDL2/SDL.h>
class Collider2d {
private:
  SDL_Rect *m_colliderRectangle{};

public:
  Collider2d();
  ~Collider2d();

  SDL_Rect &getColliderBoundingBox();
  SDL_bool isColliding(Collider2d collider);
  void setAbsolutePosition(int x, int y);
  void setDimensions(int w, int h);

  void update();
  void render();
};
#endif // !COLLIDER_2D_HPP

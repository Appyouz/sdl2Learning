#include "../include/TextureRectangle.hpp"
#include "../include/ResourceManager.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

TextureRectangle::TextureRectangle(SDL_Renderer *renderer,
                                   std::string filePath) {

  SDL_Surface *retrieveSurface =
      ResourceManager::GetInstance().GetSurface(filePath);
  std::cout << "Image loaded: " << filePath.c_str() << '\n';
  m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);

  m_rectangle.x = 0;
  m_rectangle.y = 0;
  m_rectangle.w = 32;
  m_rectangle.h = 32;
}

TextureRectangle::~TextureRectangle() { SDL_DestroyTexture(m_texture); }

void TextureRectangle::setPosition(int x, int y) {
  m_rectangle.x = x;
  m_rectangle.y = y;
}

void TextureRectangle::setDimension(int w, int h) {
  m_rectangle.w = w;
  m_rectangle.h = h;
}


SDL_bool TextureRectangle::isColliding(TextureRectangle &obj) {
  const SDL_Rect temp{obj.GetRectangle()};
  return SDL_HasIntersection(&m_rectangle, &temp);
}
void TextureRectangle::update() {}

void TextureRectangle::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}

#include "../include/TextureRectangle.hpp"
#include "../include/ResourceManager.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

TextureRectangle::TextureRectangle(SDL_Renderer *&renderer,
                                   std::string filePath) {

  SDL_Surface *retrieveSurface = ResourceManager::GetInstance().GetSurface(filePath);
  std::cout << "Image loaded: " << filePath.c_str() << '\n';
  m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);
}

TextureRectangle::~TextureRectangle() { SDL_DestroyTexture(m_texture); }

void TextureRectangle::Draw(int x, int y, int w, int h) {
  m_rectangle.x = x;
  m_rectangle.y = y;
  m_rectangle.w = w;
  m_rectangle.h = h;
}

SDL_bool TextureRectangle::isColliding(TextureRectangle& obj)
{
  const SDL_Rect temp {obj.GetRectangle()};
  return SDL_HasIntersection(&m_rectangle, &temp);
}
void TextureRectangle::update() {}

void TextureRectangle::render(SDL_Renderer *&renderer) {
  SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}

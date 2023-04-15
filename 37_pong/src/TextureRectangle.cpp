#include "../include/TextureRectangle.hpp"
#include "../include/ResourceManager.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

TextureRectangle::TextureRectangle(SDL_Renderer *renderer,
                                   std::string filePath) {

  SDL_Surface *retrieveSurface =
      ResourceManager::GetInstance().GetSurface(filePath);
  // std::cout << "Image loaded: " << filePath.c_str() << '\n';

  SDL_SetColorKey(retrieveSurface, SDL_FALSE,
                  SDL_MapRGB(retrieveSurface->format, 0xFF, 0x00, 0xFF));
  m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);
  initDefaults();
}

TextureRectangle::TextureRectangle(SDL_Renderer *renderer, std::string filePath,
                                   int redColoryKey, int greenColorKey,
                                   int blueColorKey) {

  SDL_Surface *retrieveSurface =
      ResourceManager::GetInstance().GetSurface(filePath);
  // ability to set the color key for our textured surface
  SDL_SetColorKey(retrieveSurface, SDL_TRUE,
                  SDL_MapRGB(retrieveSurface->format, redColoryKey,
                             greenColorKey, blueColorKey));
  m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);
  initDefaults();
  m_redColorKey = redColoryKey;
  m_greenColorKey = greenColorKey;
  m_blueColorKey = blueColorKey;
}

void TextureRectangle::initDefaults() {
  m_rectangle.x = 0;
  m_rectangle.y = 0;
  m_rectangle.w = 32;
  m_rectangle.h = 32;

  m_redColorKey = 0xFF;
  m_greenColorKey = 0x00;
  m_blueColorKey = 0xFF;
}
TextureRectangle::~TextureRectangle() { SDL_DestroyTexture(m_texture); }

SDL_Rect& TextureRectangle::getSDLRect(){
    return m_rectangle;
}
SDL_Rect* TextureRectangle::getSDLRectPtr(){
    return &m_rectangle;
}

SDL_Texture* TextureRectangle::getSDLTexture(){
    return m_texture;
}
void TextureRectangle::setPosition(int x, int y) {
  m_rectangle.x = x;
  m_rectangle.y = y;
}

void TextureRectangle::setDimension(int w, int h) {
  m_rectangle.w = w;
  m_rectangle.h = h;
}

int TextureRectangle::getPositionX() { return m_rectangle.x; }
int TextureRectangle::getPositionY() { return m_rectangle.y; }
int TextureRectangle::getWidth() { return m_rectangle.w; }
int TextureRectangle::getHeight() { return m_rectangle.h; }

void TextureRectangle::setColorKey(int red, int green, int blue) {}

void TextureRectangle::update() {}

void TextureRectangle::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
}

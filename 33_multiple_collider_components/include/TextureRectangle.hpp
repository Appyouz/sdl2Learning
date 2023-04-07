#ifndef TEXTURE_RECTANGLE_H
#define TEXTURE_RECTANGLE_H

#include <SDL2/SDL.h>
#include <string>

class TextureRectangle {
private:
  SDL_Rect m_rectangle;
  SDL_Texture *m_texture;
  inline SDL_Rect GetRectangle() const { return m_rectangle; }

  int m_redColorKey;
  int m_greenColorKey;
  int m_blueColorKey;

public:
  TextureRectangle(SDL_Renderer *renderer, std::string filePath);
  TextureRectangle(SDL_Renderer *renderer, std::string filePath,
                   int redColorKey, int blueColorKey, int greenColorKey);
  void initDefaults();
  ~TextureRectangle();

  void setPosition(int x, int y);
  void setDimension(int w, int h);
  int getPositionX();
  int getPositionY();
  int getWidth();
  int getHeight();

  void setColorKey(int red, int green, int blue);

  // detect collision
  void update();
  void render(SDL_Renderer *renderer);
};

#endif // !TEXTURE_RECTANGLE_H

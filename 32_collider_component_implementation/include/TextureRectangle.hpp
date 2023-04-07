#ifndef TEXTURE_RECTANGLE_H
#define TEXTURE_RECTANGLE_H

#include <string>
#include <SDL2/SDL.h>

class TextureRectangle{
private:
	SDL_Rect m_rectangle;
	SDL_Texture* m_texture;
  inline SDL_Rect GetRectangle() const {return m_rectangle;}
public:
	TextureRectangle(SDL_Renderer* renderer, std::string filePath);
	~TextureRectangle();

	void setPosition(int x, int y);
	void setDimension(int w, int h);
  int getPositionX();
  int getPositionY();
  int getWidth();
  int getHeight();

  // detect collision
	void update();
	void render(SDL_Renderer* renderer);

};

#endif // !TEXTURE_RECTANGLE_H

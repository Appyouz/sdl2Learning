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

	void Draw(int x, int y, int w, int h);

  // detect collision
  SDL_bool isColliding(TextureRectangle& obj);
	void update();
	void render(SDL_Renderer* renderer);

};

#endif // !TEXTURE_RECTANGLE_H

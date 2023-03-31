#include "TextureRectangle.hpp"

TextureRectangle::TextureRectangle(SDL_Renderer*& renderer, std::string filePath){
		SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
		m_texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		
	}
TextureRectangle::~TextureRectangle(){
		SDL_DestroyTexture(m_texture);
	}

void TextureRectangle::setRectangleProperties(int x, int y, int w, int h){
		m_rectangle.x = x;
		m_rectangle.y = y;
		m_rectangle.w = w;
		m_rectangle.h = h;
	}

void TextureRectangle::update(){

	}

void TextureRectangle::render(SDL_Renderer*& renderer){
	SDL_RenderCopy(renderer, m_texture, NULL, &m_rectangle);
	}


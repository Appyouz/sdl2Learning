#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "../include/TextureRectangle.hpp"
#include "../include/ResourceManager.hpp"

TextureRectangle::TextureRectangle(SDL_Renderer*& renderer, std::string filePath){
	
		SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface("./images/3D-Window_BBB_Blender_2.bmp");
		std::cout << "Image loaded: " << filePath.c_str() << '\n';
		m_texture = SDL_CreateTextureFromSurface(renderer, retrieveSurface);

		
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


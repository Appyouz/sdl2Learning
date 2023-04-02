#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H
#include <string>
#include <SDL2/SDL.h>

class AnimatedSprite 
{
	private:
		SDL_Rect m_src;
		SDL_Rect m_dest;
		SDL_Texture* m_texture;
	public:
		AnimatedSprite(SDL_Renderer* renderer, std::string filepath);
		~AnimatedSprite();

		void Draw(int x, int y, int w, int h);

		void PlayFrame(int x, int y, int w,int h, int frame);
		void Update();
		void Render(SDL_Renderer*& renderer);
};

#endif // !ANIMATED_SPRITE_H

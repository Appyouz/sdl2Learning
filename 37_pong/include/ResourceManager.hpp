#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <iostream>
#include <SDL2/SDL.h>
#include <unordered_map>
class ResourceManager 
{
	private:
		ResourceManager();
		ResourceManager(ResourceManager const&);
		ResourceManager operator=(ResourceManager const&);

		std::unordered_map<std::string, SDL_Surface*> m_surfaces;

	public:
		static ResourceManager& GetInstance();

		SDL_Surface* GetSurface(std::string filepath);
};

#endif // !RESOURCE_MANAGER_H

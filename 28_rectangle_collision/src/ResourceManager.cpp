#include "../include/ResourceManager.hpp"


ResourceManager::ResourceManager()
{

}
ResourceManager::ResourceManager(ResourceManager const&)
{

}

ResourceManager ResourceManager::operator=(ResourceManager const&)
{
	return *this;
}

// instantiate exactl one instance of our class
ResourceManager& ResourceManager:: GetInstance()
{
	static ResourceManager* s_instance {new ResourceManager};
	return *s_instance;
}

SDL_Surface* ResourceManager::GetSurface(std::string filepath)
{
	// look through m_surfaces(unordered map) and see
	// if a file exits, and if file exists return associated surface
	auto search {m_surfaces.find(filepath)};
	if(search != m_surfaces.end()){
		return m_surfaces[filepath];
	}else{
		SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
		m_surfaces.insert(std::make_pair(filepath, surface));
		return m_surfaces[filepath];
	}
	return nullptr;
}


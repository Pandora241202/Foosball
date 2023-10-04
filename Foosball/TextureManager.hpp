#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Game.hpp"

class TextureManager {
public:
	static SDL_Texture* LoadImage(const char* fileName, SDL_Renderer* renderer);
};

#endif

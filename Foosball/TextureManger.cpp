#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadImage(const char* fileName, SDL_Renderer* renderer) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return text;
}
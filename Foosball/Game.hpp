#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>

const int BALL_RADIUS = 8;

class Game {
public:
	Game();
	~Game();

	void start(const char* title, int w, int h);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

private:
	bool run;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // !Game_hpp

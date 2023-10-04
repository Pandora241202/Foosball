#ifndef Ball_hpp
#define Ball_hpp

#include "Game.hpp"
#include "Vector2D.hpp"

enum posOfBar { UPBAR, DOWNBAR, LEFTBAR, RIGHTBAR };

class Ball {
private:
	SDL_Texture* ballTexture;
	SDL_Rect dstRect;
	SDL_Renderer* renderer;
	Vector2D* v;

public:
	Ball(SDL_Renderer* rend);
	~Ball();

	void Move();
	int TouchBar();
	void ChangeDirectWhenTouchBar(int pos);
	bool InRedTeamGoal();
	bool InBlueTeamGoal();
	void Render();
};

#endif
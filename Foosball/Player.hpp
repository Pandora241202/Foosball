#ifndef Player_hpp
#define Player_hpp

#include "Game.hpp"

enum posOnPole {
	POS0ONPOLE = 125,
	POS1ONPOLE = 205,
	POS2ONPOLE = 285,
	POS3ONPOLE = 360,
	POS4ONPOLE = 440,
};

enum playerState {NORMAL, KICKRIGHT, KICKLEFT};

class Player {
private:
	SDL_Texture* playerTexture;
	SDL_Rect dstRect;
	SDL_Renderer* renderer;
	playerState state;

public:
	Player(SDL_Renderer* rend, int posPole, int posYard, bool isRedTeam);
	~Player();

	void Move(int distance);
	void KickRight(bool isRedTeam, int posYard);
	void KickLeft(bool isRedTeam, int posYard);
	void Normal(bool isRedTeam, int posYard);

	void Render();
};

#endif

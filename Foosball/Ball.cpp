#include "Ball.hpp"
#include "TextureManager.hpp"

Ball::Ball(SDL_Renderer* rend) {
	renderer = rend;

	ballTexture = TextureManager::LoadImage("Images/ball.png", renderer);

	dstRect.x = 489;
	dstRect.y = 289;
	dstRect.w = 22;
	dstRect.h = 22;

	v = new Vector2D(1, 4);
}

Ball::~Ball() {}

void Ball::Move() {
	if (dstRect.y + v->y >= 216 && dstRect.y + v->y + 22 <= 384) {
		dstRect.x += v->x;
		dstRect.y += v->y;
		return;
	}
	dstRect.x = dstRect.x + v->x - 100 < 0 ? 100 : 900 - dstRect.x - v->x < 22 ? 878 : dstRect.x + v->x;
	dstRect.y = dstRect.y + v->y - 100 < 0 ? 100 : 500 - dstRect.y - v->y < 22 ? 478 : dstRect.y + v->y;
}

int Ball::TouchBar() {
	if (dstRect.x - 100 == 0 && (dstRect.y + 11 < 216 || dstRect.y - 11 > 384)) {
		return LEFTBAR;
	}
	if (900 - dstRect.x == 22 && (dstRect.y + 11 < 216 || dstRect.y - 11 > 384)) {
		return RIGHTBAR;
	}
	if (dstRect.y - 100 == 0) {
		return UPBAR;
	}
	if (500 - dstRect.y == 22) {
		return DOWNBAR;
	}
	return -1;
}

void Ball::ChangeDirectWhenTouchBar(int pos) {
	Vector2D* n = nullptr;

	switch(pos) {
	case UPBAR:
		n = new Vector2D(0, 1);
		break;
	case DOWNBAR:
		n = new Vector2D(0, -1);
		break;
	case LEFTBAR:
		n = new Vector2D(1, 0);
		break;
	case RIGHTBAR:
		n = new Vector2D(-1, 0);
		break;
	}

	v = *v - n->MUL(v->DOT(n))->MUL(2);
}

bool Ball::InBlueTeamGoal() {
	return dstRect.x + 11 <= 100;
}

bool Ball::InRedTeamGoal() {
	return dstRect.x + 11 >= 900;
}

void Ball::Render() {
	SDL_RenderCopy(renderer, ballTexture, NULL, &dstRect);
}
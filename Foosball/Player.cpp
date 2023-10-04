#include "Player.hpp"
#include "TextureManager.hpp"

Player::Player(SDL_Renderer* rend, int posPole, int posYard, bool isRedTeam) {
	renderer = rend;

	playerTexture = TextureManager::LoadImage(isRedTeam ? "Images/redPlayer.png" : "Images/bluePlayer.png", renderer);
	
	dstRect.x = posYard - 2;
	dstRect.y = posPole;
	dstRect.w = 17;
	dstRect.h = 30;

	state = NORMAL;
}

Player::~Player() {}

void Player::Move(int distance) {
	dstRect.y += distance;
}

void Player::KickLeft(bool isRedTeam, int posYard) {
	dstRect.x = posYard - 15;
	dstRect.w = 41;
	dstRect.h = 30;
	playerTexture = TextureManager::LoadImage(isRedTeam ? "Images/redPlayerKickLeft.png" : "Images/bluePlayerKickLeft.png", renderer);
	state = KICKLEFT;
}

void Player::KickRight(bool isRedTeam, int posYard) {
	dstRect.x = posYard - 10;
	dstRect.w = 41;
	dstRect.h = 30;
	playerTexture = TextureManager::LoadImage(isRedTeam ? "Images/redPlayerKickRight.png" : "Images/bluePlayerKickRight.png", renderer);
	state = KICKRIGHT;
}

void Player::Normal(bool isRedTeam, int posYard) {
	dstRect.x = posYard - 2;
	dstRect.w = 17;
	dstRect.h = 30;
	playerTexture = TextureManager::LoadImage(isRedTeam ? "Images/redPlayer.png" : "Images/bluePlayer.png", renderer);
	state = NORMAL;
}

void Player::Render() {
	SDL_RenderCopy(renderer, playerTexture, NULL, &dstRect);
}
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Yard.hpp"
#include "BlockBars.hpp"
#include "PlayerPole.hpp"
#include "Player.hpp"
#include "Ball.hpp"

Game::Game() {}

Game::~Game() {}

Yard* yard;
BlockBars* bars;
PlayerPole* redTeam[4];
PlayerPole* blueTeam[4];
Ball* ball;

int red = 0, blue = 0;

const int MOVE_DISTANCE = 5;

void Game::start(const char* title, int w, int h) {	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystem initialized..." << std::endl;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
		if (window) {
			std::cout << "Window created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "Renderer created..." << std::endl;
		}

		run = true;
	}
	else {
		run = false;
	}

	yard = new Yard(renderer);
	
	redTeam[0] = new PlayerPole(renderer, true, POS2ONYARD, 3);
	redTeam[1] = new PlayerPole(renderer, true, POS4ONYARD, 5);
	redTeam[2] = new PlayerPole(renderer, true, POS6ONYARD, 2);
	redTeam[3] = new PlayerPole(renderer, true, POS7ONYARD, 1);
	
	blueTeam[0] = new PlayerPole(renderer, false, POS0ONYARD, 1);
	blueTeam[1] = new PlayerPole(renderer, false, POS1ONYARD, 2);
	blueTeam[2] = new PlayerPole(renderer, false, POS3ONYARD, 5);
	blueTeam[3] = new PlayerPole(renderer, false, POS5ONYARD, 3);
	
	bars = new BlockBars(renderer);

	ball = new Ball(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		run = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			for (int i = 0; i < 4; i++) {
				blueTeam[i]->Move(-MOVE_DISTANCE);
			}
			break;
		case SDLK_DOWN:
			for (int i = 0; i < 4; i++) {
				blueTeam[i]->Move(MOVE_DISTANCE);
			}
			break;
		case SDLK_LEFT:
			for (int i = 0; i < 4; i++) {
				blueTeam[i]->KickLeft();
			}
			break;
		case SDLK_RIGHT:
			for (int i = 0; i < 4; i++) {
				blueTeam[i]->KickRight();
			}
			break;
		}
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) {
			for (int i = 0; i < 4; i++) {
				blueTeam[i]->Normal();
			}
		}
	}
}

void Game::update() {
	if (ball->InRedTeamGoal()) {
		blue += 1;
		ball->~Ball();
		ball = new Ball(renderer);
		return;
	}
	if (ball->InBlueTeamGoal()) {
		red += 1;
		ball->~Ball();
		ball = new Ball(renderer);
		return;
	}
	int bar = ball->TouchBar();
	if (bar != -1) {
		ball->ChangeDirectWhenTouchBar(bar);
	}
	ball->Move();
	std::cout << "red" << red << " " << "blue" << blue;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 54, 25, 35, 255);
	SDL_RenderClear(renderer);	
	
	yard->Render();

	ball->Render();

	for (int i = 0; i < 4; i++) {
		redTeam[i]->Render();
	}
	for (int i = 0; i < 4; i++) {
		blueTeam[i]->Render();
	}

	bars->Render();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

bool Game::running() {
	return run;
}

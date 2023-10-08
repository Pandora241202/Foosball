#include "Game.hpp"
#include "TextureManager.hpp"
#include "Yard.hpp"
#include "BlockBars.hpp"
#include "Team.hpp"
#include "Ball.hpp"


Game::Game() {}

Game::~Game() {}

Yard *yard;
BlockBars *bars;
Team *blueTeam, *redTeam;
Ball *ball;

const char* score[8] = {"0", "1", "2", "3", "4", "5", "6", "7"};
TTF_Font* font = nullptr;
SDL_Texture *redScoreTexture, *blueScoreTexture;
SDL_Rect redScoreRect, blueScoreRect;

const int MOVE_DISTANCE = 7;

void Game::start(const char* title, int w, int h) {	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || !font) run = false;
	
	std::cout << "Subsystem initialized..." << std::endl;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (window) {
		std::cout << "Window created..." << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer) {
		std::cout << "Renderer created..." << std::endl;
	}

	TTF_Init();
	font = TTF_OpenFont("Fonts/pixel-gaming-font/PixelGamingRegular-d9w0g.ttf", 30);

	run = true;

	yard = new Yard(renderer);
	
	blueTeam = new Team(renderer, true);
	redTeam = new Team(renderer, false);

	bars = new BlockBars(renderer);

	ball = new Ball(renderer);

	redScoreRect.x = 520;
	redScoreRect.y = 10;
	redScoreRect.w = 30;
	redScoreRect.h = 40;

	blueScoreRect.x = 450;
	blueScoreRect.y = 10;
	blueScoreRect.w = 30;
	blueScoreRect.h = 40;

	redScoreTexture = TextureManager::LoadText(score[redTeam->GetScore()], renderer, { 126, 0 ,21 }, font);
	blueScoreTexture = TextureManager::LoadText(score[blueTeam->GetScore()], renderer, { 63, 72, 204 }, font);
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
			redTeam->Move(-MOVE_DISTANCE);
			break;
		case SDLK_DOWN:
			redTeam->Move(MOVE_DISTANCE);
			break;
		case SDLK_w:
			blueTeam->Move(-MOVE_DISTANCE);
			break;
		case SDLK_s:
			blueTeam->Move(MOVE_DISTANCE);
			break;
		}
	}
}

void Game::update() {
	if (ball->InRedTeamGoal()) {
		blueTeam->AddScore();
		blueScoreTexture = TextureManager::LoadText(score[blueTeam->GetScore()], renderer, { 63, 72, 204 }, font);
		ball->~Ball();
		ball = new Ball(renderer);
		return;
	}
	if (ball->InBlueTeamGoal()) {
		redTeam->AddScore();
		redScoreTexture = TextureManager::LoadText(score[redTeam->GetScore()], renderer, { 126, 0 ,21 }, font);
		ball->~Ball();
		ball = new Ball(renderer);
		return;
	}

	ball->CheckCollideBar();
	ball->CheckCollidePlayerInTeam(redTeam);
	ball->CheckCollidePlayerInTeam(blueTeam);

	ball->Move();
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 164, 168, 119, 255);
	SDL_RenderClear(renderer);

	yard->Render();

	ball->Render();

	blueTeam->Render();
	redTeam->Render();

	bars->Render();

	SDL_RenderCopy(renderer, redScoreTexture, nullptr, &redScoreRect);
	SDL_RenderCopy(renderer, blueScoreTexture, nullptr, &blueScoreRect);

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

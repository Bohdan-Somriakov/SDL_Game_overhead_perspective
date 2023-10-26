//third-party libraries
#include "SDL.h"
#include "SDL_image.h"
//standard libraries
#include <string>
#include <iostream>
#include <cmath>
//file includes
#include "Header.h"
Player::Player(SDL_Renderer* renderTarget, const char* filePath, int x, int y, int framesX, int framesY, int totalFramesX, int totalFramesY, int widthFactor, int heightFactor) {

	//framesX and framesY is the number of frames in one animation
	//this project uses sprite sheets (single texture) thus
	//totalFramesX and totalFramesY is the total number of frames
	//in the picture (walking, attack, die, bow etc...)

	texture = loadTexture(filePath, renderTarget);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	cropRect.w /= totalFramesX;
	cropRect.h /= totalFramesY;

	positionRect.x = x;
	positionRect.y = y;

	positionRect.w = cropRect.w * widthFactor;
	positionRect.h = cropRect.h * heightFactor;

	textureWidth = cropRect.w * totalFramesX;

	frameWidth = cropRect.w;
	frameHeight = cropRect.h;

	isActive = false;
	isAttacking = false;

	originX = frameWidth / 2 * widthFactor;
	originY = frameHeight / 2 * heightFactor;

	radius = frameWidth / 2;

	static int playerNumber = 0;
	playerNumber++;

	if (playerNumber == 1) {
		keys[0] = SDL_SCANCODE_W;
		keys[1] = SDL_SCANCODE_S;
		keys[2] = SDL_SCANCODE_A;
		keys[3] = SDL_SCANCODE_D;
		keys[4] = SDL_SCANCODE_SPACE;
	}
	else if (playerNumber == 2) {
		keys[0] = SDL_SCANCODE_UP;
		keys[1] = SDL_SCANCODE_DOWN;
		keys[2] = SDL_SCANCODE_LEFT;
		keys[3] = SDL_SCANCODE_RIGHT;
		keys[4] = SDL_SCANCODE_PERIOD;
	}
	moveSpeed = 200.0f; //mb change to 150.0f
}
void Player::Update(float delta, const Uint8* keyState) {
	isActive = true;
	//Since positionRect is supposed to represent an area on the screen,
	//a positionRect object can only store integral data.
	//Since a floating point number is truncated when stored as an integer,
	//it appears to move faster in the negative direction (left and up).
	//THAT'S WHY WE NEED TO TYPE int(moveSpeed * delta)
	if (keyState[keys[0]] && keyState[keys[3]]) {
		positionRect.y -= int(moveSpeed * delta / sqrt(2));
		positionRect.x += int(moveSpeed * delta / sqrt(2));
		cropRect.y = frameHeight * 3;
	}
	else if (keyState[keys[1]] && keyState[keys[3]]) {
		positionRect.y += int(moveSpeed * delta / sqrt(2));
		positionRect.x += int(moveSpeed * delta / sqrt(2));
		cropRect.y = frameHeight;
	}
	else if (keyState[keys[1]] && keyState[keys[2]]) {
		positionRect.y += int(moveSpeed * delta / sqrt(2));
		positionRect.x -= int(moveSpeed * delta / sqrt(2));
		cropRect.y = frameHeight * 7;
	}
	else if (keyState[keys[0]] && keyState[keys[2]]) {
		positionRect.y -= int(moveSpeed * delta / sqrt(2));
		positionRect.x -= int(moveSpeed * delta / sqrt(2));
		cropRect.y = frameHeight * 5;
	}
	else if (keyState[keys[0]]) {
		positionRect.y -= int(moveSpeed * delta);
		cropRect.y = frameHeight * 4;
	}
	else if (keyState[keys[1]]) {
		positionRect.y += int(moveSpeed * delta);
		cropRect.y = 0;
	}
	else if (keyState[keys[2]]) {
		positionRect.x -= int(moveSpeed * delta);
		cropRect.y = frameHeight * 6;
	}
	else if (keyState[keys[3]]) {
		positionRect.x += int(moveSpeed * delta);
		cropRect.y = frameHeight * 2;
	}
	else {
		isActive = false;
	}

	if (keyState[keys[4]] && !keyState[keys[0]] && !keyState[keys[1]] && !keyState[keys[2]] && !keyState[keys[3]]) {
		isAttacking = true;
		cropRect.x = frameWidth * 4;
	}

	if (isAttacking) {

		frameCounter += delta;

		if (frameCounter >= 0.25f) {

			frameCounter = 0;

			cropRect.x += frameWidth;

			if (cropRect.x >= textureWidth / 6 * 2) { //2 is because the next set of sprites stands for attack
				cropRect.x = 0;
				isAttacking = false;
			}
		}

	}

	if (isActive) {

		isAttacking = false;

		frameCounter += delta;

		if (frameCounter >= 0.25f) {
			frameCounter = 0;
			cropRect.x += frameWidth;
			if (cropRect.x >= textureWidth / 6) {
				cropRect.x = 0;
			}
		}
	}
	else {
		if (!isAttacking) {
			frameCounter = 0;
			cropRect.x = frameWidth;
		}
	}
}
//void Player::Draw(SDL_Renderer* renderTarget) {}
Player::~Player() {
	std::cout << "Player was destroyed " << texture << '\n';
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
void Player::Draw(SDL_Renderer* renderTarget) {
	GameObject::Draw(renderTarget);
}
void Player::Block(float delta, const Uint8* keyState) {
		// Handle blocking movement or any other desired behavior here
		if (keyState[keys[0]] && keyState[keys[3]]) {
			positionRect.y += int(moveSpeed * delta / sqrt(2));
			positionRect.x -= int(moveSpeed * delta / sqrt(2));
			cropRect.y = frameHeight * 3;
		}
		else if (keyState[keys[1]] && keyState[keys[3]]) {
			positionRect.y -= int(moveSpeed * delta / sqrt(2));
			positionRect.x -= int(moveSpeed * delta / sqrt(2));
			cropRect.y = frameHeight;
		}
		else if (keyState[keys[1]] && keyState[keys[2]]) {
			positionRect.y -= int(moveSpeed * delta / sqrt(2));
			positionRect.x += int(moveSpeed * delta / sqrt(2));
			cropRect.y = frameHeight * 7;
		}
		else if (keyState[keys[0]] && keyState[keys[2]]) {
			positionRect.y += int(moveSpeed * delta / sqrt(2));
			positionRect.x += int(moveSpeed * delta / sqrt(2));
			cropRect.y = frameHeight * 5;
		}
		else if (keyState[keys[0]]) {
			positionRect.y += int(moveSpeed * delta);
			cropRect.y = frameHeight * 4;
		}
		else if (keyState[keys[1]]) {
			positionRect.y -= int(moveSpeed * delta);
			cropRect.y = 0;
		}
		else if (keyState[keys[2]]) {
			positionRect.x += int(moveSpeed * delta);
			cropRect.y = frameHeight * 6;
		}
		else if (keyState[keys[3]]) {
			positionRect.x -= int(moveSpeed * delta);
			cropRect.y = frameHeight * 2;
		}
		else {
			isActive = false;
		}
	}
void Player::Attack(float delta, const Uint8* keyState, SDL_Renderer* renderTarget) {
	if (keyState[keys[4]]) {
		cropRect.x = frameWidth * 4;
	}
};
SDL_Texture* Player::GetTexture() {
	return GameObject::GetTexture();
}
int Player::GetOriginX() {
	return GameObject::GetOriginX();
};
int Player::GetOriginY() {
	return GameObject::GetOriginY();
}
int Player::GetRadius() {
	return GameObject::GetRadius();
}
int Player::GetID() {
	return GameObject::GetID();
}
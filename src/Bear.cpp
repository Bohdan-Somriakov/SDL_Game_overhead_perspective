#include "Bear.h"
#include "Header.h"
Bear::Bear(SDL_Renderer* renderTarget, const char* filePath, int x, int y, int framesX, int framesY, int widthFactor, int heightFactor) {
	texture = loadTexture(filePath, renderTarget);

	SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

	cropRect.w /= framesX;
	cropRect.h /= framesY;

	positionRect.x = x;
	positionRect.y = y;

	positionRect.w = cropRect.w * widthFactor;
	positionRect.h = cropRect.h * heightFactor;

	textureWidth = cropRect.w * framesX;

	frameWidth = cropRect.w;
	frameHeight = cropRect.h;

	isActive = false;
	isAttacking = false;

	originX = frameWidth / 2 * widthFactor;
	originY = frameHeight / 2 * heightFactor;

	radius = frameWidth / 2;

	moveSpeed = 150.0f; // mb change to 200
}
void Bear::Update(float delta) {

	srand(time(NULL));
	static int steps = 0;

	if (rand() % 7 == 1 && !steps) { //0,1,2,3,4
		direction = "RIGHT";
		steps = rand() % 200;
		isActive = true;
	}
	else if (rand() % 7 == 2 && !steps) {
		direction = "DOWN";
		steps = rand() % 200;
		isActive = true;
	}
	else if (rand() % 7 == 3 && !steps) {
		direction = "LEFT";
		steps = rand() % 200;
		isActive = true;
	}
	else if (rand() % 7 == 4 && !steps) {
		direction = "UP";
		steps = rand() % 200;
		isActive = true;
	}
	else if ((rand() % 7 == 0) || (rand() % 7 == 5) || (rand() % 7 == 6) && !steps) {
		direction = "STOP";
		steps = rand() % 200;
		isActive = false;
	}

	if (steps > 0) {
		steps--;

		if (direction == "RIGHT") {
			cropRect.y = 0;
			positionRect.x += static_cast<int>(moveSpeed * delta);
		}
		else if (direction == "DOWN") {
			cropRect.y = cropRect.w * 3;
			positionRect.y += static_cast<int>(moveSpeed * delta);
		}
		else if (direction == "LEFT") {
			cropRect.y = cropRect.w;
			positionRect.x -= static_cast<int>(moveSpeed * delta);
		}
		else if (direction == "UP") {
			cropRect.y = cropRect.w * 2;
			positionRect.y -= static_cast<int>(moveSpeed * delta);
		} 
		else if (direction == "STOP") {
			//maybe add some animation
		}

		frameCounter += delta;

		if (frameCounter >= 0.25f && isActive) {

			frameCounter = 0;

			cropRect.x += cropRect.w;

			if (cropRect.x >= textureWidth) {
				cropRect.x = 0;
			}

		}

	}
	
}
void Bear::Block(float delta) {
	if (direction == "RIGHT") {
		cropRect.y = 0;
		positionRect.x -= static_cast<int>(moveSpeed * delta);
	}
	else if (direction == "DOWN") {
		cropRect.y = cropRect.w * 3;
		positionRect.y -= static_cast<int>(moveSpeed * delta);
	}
	else if (direction == "LEFT") {
		cropRect.y = cropRect.w;
		positionRect.x += static_cast<int>(moveSpeed * delta);
	}
	else if (direction == "UP") {
		cropRect.y = cropRect.w * 2;
		positionRect.y += static_cast<int>(moveSpeed * delta);
	}
	else if (direction == "STOP") {
		//maybe add some animation
	}
}
Bear::~Bear() {
	std::cout << "Player was destroyed " << texture << '\n';
	SDL_DestroyTexture(texture);
	texture = nullptr;
}
void Bear::Draw(SDL_Renderer* renderTarget) {
	GameObject::Draw(renderTarget);
}
int Bear::GetOriginX() {
	return GameObject::GetOriginX();
}
int Bear::GetOriginY() {
	return GameObject::GetOriginY();
}
int Bear::GetRadius() {
	return GameObject::GetRadius();
}
SDL_Texture* Bear::GetTexture() {
	return GameObject::GetTexture();
}
int Bear::GetID() {
	return GameObject::GetID();
}
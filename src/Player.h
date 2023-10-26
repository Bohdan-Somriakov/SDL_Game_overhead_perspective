#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "Header.h"
#include "GameObject.h"

class Player : public GameObject {
	float moveSpeed;
	float frameCounter;
	int frameWidth;
	int frameHeight;
	int textureWidth;
	float delta;
	SDL_Scancode keys[5];
	bool isActive;
	bool isAttacking;
public:
	Player(SDL_Renderer* renderTarget, const char* filePath, int x, int y, int framesX, int framesY, int totalFramesX,int totalFramesY, int widthFactor, int heightFactor);
	~Player();
	void Update(float delta, const Uint8* keyState);
	void Draw(SDL_Renderer* renderTarget)override;
	void Block(float delta, const Uint8* keyState);
	void Attack(float delta, const Uint8* keyState, SDL_Renderer* renderTarget);
	SDL_Texture* GetTexture()override;
	int GetOriginX()override;
	int GetOriginY()override;
	int GetRadius()override;
	int GetID()override;
};

#endif
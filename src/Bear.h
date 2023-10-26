#ifndef BEAR_h
#define BEAR_h

#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"

class Bear : public GameObject {
private:
	float moveSpeed;
	float frameCounter;
	int frameWidth;
	int frameHeight;
	int textureWidth;
	float delta;
	bool isActive;
	bool isAttacking;
	std::string direction;
public:
	Bear(SDL_Renderer* renderTarget, const char* filePath, int x, int y, int framesX, int framesY, int widthFactor, int heightFactor);
	~Bear();
	void Update(float delta);
	void Draw(SDL_Renderer* renderTarget)override;
	void Block(float delta);
	void Attack(float delta, const Uint8* keyState, SDL_Renderer* renderTarget);
	SDL_Texture* GetTexture()override;
	int GetOriginX()override;
	int GetOriginY()override;
	int GetRadius()override;
	int GetID()override;
};

#endif 

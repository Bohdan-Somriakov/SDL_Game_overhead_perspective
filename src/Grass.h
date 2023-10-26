#ifndef GRASS_H
#define GRASS_H

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "GameObject.h"

class Grass : public GameObject {

public:
    Grass();
    Grass(std::string filePath, int x, int y, int widthFactor, int heightFactor, SDL_Renderer* renderer);
    Grass(const Grass& other);
    Grass(Grass&& other) noexcept;
    Grass& operator=(const Grass& other);
    Grass& operator=(Grass&& other) noexcept;
    ~Grass();

    SDL_Texture* GetTexture()override;
    int GetID()override;
};

#endif
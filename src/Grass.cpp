#include "SDL.h"
#include "SDL_image.h"
#include "Header.h"
#include <iostream>
#include <string>

Grass::Grass() { texture = nullptr; }

    Grass::Grass(std::string filePath, int x, int y, int widthFactor, int heightFactor, SDL_Renderer* renderer) {
        texture = loadTexture(filePath.c_str(), renderer);
        SDL_QueryTexture(texture, NULL, NULL, &positionRect.w, &positionRect.h);
        positionRect.x = x;
        positionRect.y = y;
        positionRect.w*= widthFactor;
        positionRect.h*= heightFactor;
    }

    //Copy Constructor
    Grass::Grass(const Grass& other) {

        texture = other.texture;

        positionRect.x = other.positionRect.x;
        positionRect.y = other.positionRect.y;
        positionRect.w = other.positionRect.w;
        positionRect.h = other.positionRect.h;

        ID = other.ID;

        if (texture) {
            SDL_QueryTexture(texture, NULL, NULL, &positionRect.w, &positionRect.h);
        }
    }

    //Move Constructor
    Grass::Grass(Grass&& other) noexcept {

        texture = other.texture;

        positionRect.x = other.positionRect.x;
        positionRect.y = other.positionRect.y;
        positionRect.w = other.positionRect.w;
        positionRect.h = other.positionRect.h;

        ID = other.ID;

        other.texture = nullptr;
        other.positionRect = SDL_Rect{};
    }

    //Copy Assignment Operator
    Grass& Grass::operator=(const Grass& other) {
        if (this != &other) {
            texture = other.texture;
            positionRect = other.positionRect;
            if (texture) {
                SDL_QueryTexture(texture, NULL, NULL, &positionRect.w, &positionRect.h);
            }
        }
        return *this;
    }

    //Move Assignment Operator
    Grass& Grass::operator=(Grass&& other) noexcept {
        if (this != &other) {
            SDL_DestroyTexture(texture);

            texture = other.texture;
            positionRect = other.positionRect;

            other.texture = nullptr;
            other.positionRect = SDL_Rect{};
        }
        return *this;
    }

    Grass::~Grass() {
        std::cout << "Grass was destroyed " << texture << '\n';
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Texture* Grass::GetTexture() {
        return GameObject::GetTexture();
    }
    int Grass::GetID() {
        return GameObject::GetID();
    }
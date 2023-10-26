#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
inline SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filePath);
    if (surface == nullptr) {
        std::cout << "Error loading texture from: " << filePath << "\n";
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        std::cout << "Error creating texture from surface: " << SDL_GetError() << "\n";
        return nullptr;
    }

    return texture;
}
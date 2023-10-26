#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Header.h"

    Tree::Tree() { texture = nullptr; }

    Tree::Tree(std::string filePath, int x, int y, int widthFactor, int heightFactor, SDL_Renderer* renderer) {
        texture = loadTexture(filePath.c_str(), renderer);
        SDL_QueryTexture(texture, NULL, NULL, &positionRect.w, &positionRect.h);

        positionRect.x = x;
        positionRect.y = y;

        positionRect.w *= widthFactor;
        positionRect.h *= heightFactor;
        
        originX = positionRect.w / 2;
        originY = positionRect.h / 2;

        radius = positionRect.w / 2;

    }

    //Copy Constructor
    Tree::Tree(const Tree& other) {

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
    Tree::Tree(Tree&& other) noexcept {

        texture = other.texture;

        positionRect.x = other.positionRect.x;
        positionRect.y = other.positionRect.y;
        positionRect.w = other.positionRect.w;
        positionRect.h = other.positionRect.h;

        other.texture = nullptr;
        other.positionRect = SDL_Rect{};

        originX = positionRect.w / 2;
        originY = positionRect.h / 2;

        radius = positionRect.w / 2;

        ID = other.ID;
    }

    //Copy Assignment Operator
        Tree& Tree::operator=(const Tree& other) {
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
    Tree& Tree::operator=(Tree&& other) noexcept {
        if (this != &other) {
            SDL_DestroyTexture(texture);

            texture = other.texture;
            positionRect = other.positionRect;

            other.texture = nullptr;
            other.positionRect = SDL_Rect{};
        }
        return *this;
    }

    Tree::~Tree() {
        std::cout << "Tree was destroyed " << texture << '\n';
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Texture* Tree::GetTexture() {
        return GameObject::GetTexture();
    }
    int Tree::GetOriginX() {
        return GameObject::GetOriginX();
    }
    int Tree::GetOriginY() {
        return GameObject::GetOriginY();
    }
    int Tree::GetRadius() {
        return GameObject::GetRadius();
    }
    int Tree::GetID() {
        return GameObject::GetID();
    }
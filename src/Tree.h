#ifndef TREE_H
#define TREE_H

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "GameObject.h"

class Tree : public GameObject {

public:
    Tree();
    Tree(std::string filePath, int x, int y, int widthFactor, int heightFactor, SDL_Renderer* renderer);
    Tree(const Tree& other);
    Tree(Tree&& other) noexcept;
    Tree& operator=(const Tree& other);
    Tree& operator=(Tree&& other) noexcept;
    ~Tree();

    SDL_Texture* GetTexture()override;
    int GetOriginX()override;
    int GetOriginY()override;
    int GetRadius()override;
    int GetID()override;
};

#endif
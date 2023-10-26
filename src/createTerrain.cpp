#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Header.h"

inline void createGrass(SDL_Renderer* renderer, int levelWidth, int levelHeight, std::vector<Grass*>& grasses, int widthFactor, int heightFactor, std::vector<GameObject*>& gameObjects) {
    srand(time(NULL));
    int textureWidth, textureHeight;
    SDL_Texture* grassTexture = loadTexture("assets/Puny-Characters/Environment/Grass1.png", renderer);
    SDL_QueryTexture(grassTexture, NULL, NULL, &textureWidth, &textureHeight);
    textureWidth *= widthFactor;
    textureHeight *= heightFactor;
    SDL_Rect texturePosition = { 0, 0, textureWidth, textureHeight };

    while (true) {
        std::string textureToAdd;

        if (rand() % 2 == 1) {
            textureToAdd = "assets/Puny-Characters/Environment/Grass1.png";
        }
        else {
            textureToAdd = "assets/Puny-Characters/Environment/Grass2.png";
        }

        Grass* grassElem = new Grass(textureToAdd, texturePosition.x, texturePosition.y, widthFactor, heightFactor, renderer);
        grasses.push_back(grassElem);

        std::cout << "Generating Grass...  " << grassElem->GetTexture() << std::endl;

        texturePosition.x += textureWidth;
        if (texturePosition.x >= levelWidth) {
            texturePosition.x = 0;
            texturePosition.y += textureHeight;
        }

        if (texturePosition.y >= levelHeight) {
            for (Grass* grassElem : grasses) {
               SDL_RenderCopy(renderer, grassElem->GetTexture(), NULL, &grassElem->positionRect);
               gameObjects.push_back(grassElem);
            }
            return;
        }
    }
}

inline void createForest(SDL_Renderer* renderer, int levelWidth, int levelHeight, std::vector<Tree*>& trees, int widthFactor, int heightFactor, std::vector<GameObject*>& gameObjects) {
    srand(time(NULL));
    int textureWidth, textureHeight;
    SDL_Texture* treeTexture = loadTexture("assets/Puny-Characters/Environment/Tree.png", renderer);
    SDL_QueryTexture(treeTexture, NULL, NULL, &textureWidth, &textureHeight);
    textureWidth *= widthFactor;
    textureHeight *= heightFactor;
    SDL_Rect texturePosition = { 0, 0, textureWidth, textureHeight };

    while (true) {
        std::string textureToAdd;

        if (rand() % 10 == 9) {
            textureToAdd = "assets/Puny-Characters/Environment/Tree.png";
        }

        Tree* treeElem = nullptr;

        if (!textureToAdd.empty()) {
            treeElem = new Tree(textureToAdd, texturePosition.x, texturePosition.y, widthFactor, heightFactor, renderer);
        }

        if (!textureToAdd.empty()) {
            trees.push_back(treeElem);
            std::cout << "Generating Forest...  " << treeElem->GetTexture() << std::endl;
        } 

        texturePosition.x += textureWidth;
        if (texturePosition.x >= levelWidth) {
            texturePosition.x = 0;
            texturePosition.y += textureHeight;
        }

        if (texturePosition.y >= levelHeight) {
            for (Tree* tree : trees) {
                SDL_RenderCopy(renderer, tree->GetTexture(), NULL, &tree->positionRect);
                gameObjects.push_back(tree);
            }
            return;
        }
    }
}

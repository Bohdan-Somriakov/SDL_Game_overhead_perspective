#include "SDL.h"
#include "SDL_image.h"

#include "Grass.h"
#include "Player.h"
#include "loadTexture.cpp"
#include "createTerrain.cpp"
#include "randomSpawnCoords.cpp"
#include "createAnimals.cpp"

#include <vector>
#include <iostream>
#include <string>
#include "Bear.h"
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    int imgFlags = (IMG_INIT_PNG | IMG_INIT_JPG);
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "Error " << IMG_GetError() << '\n';
        return 1;
    }

    std::vector<GameObject*> gameObjects;

    const int levelWidth = 1280; // 1,280 or 640
    const int levelHeight = 720; // 720 or 480

    float currentTime = 0.0f;
    float prevTime = 0.0f;
    float deltaTime = 0.0f;
    const Uint8* keyState;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderTarget = nullptr;
    SDL_Texture* spriteSheetTexture = nullptr;
    SDL_Texture* texture1 = nullptr;


    window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, levelWidth, levelHeight, SDL_WINDOW_SHOWN);
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    spriteSheetTexture = SDL_CreateTexture(renderTarget, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, levelWidth, levelHeight);
    SDL_SetRenderTarget(renderTarget, spriteSheetTexture);
    std::vector<Grass*> grasses;
    std::vector<Tree*> trees;
    std::vector<Bear*> bears;
    createGrass(renderTarget, levelWidth, levelHeight, grasses, 4, 4, gameObjects);
    createForest(renderTarget, levelWidth, levelHeight, trees, 4, 4, gameObjects);
    createBears(renderTarget, bears, levelWidth, levelHeight, gameObjects);
    SDL_SetRenderTarget(renderTarget, NULL);

    SDL_Event ev{};
    bool isRunning = true;

    int xSpawn = 0, ySpawn = 0;
    randomSpawnCoords(xSpawn, ySpawn, gameObjects, levelWidth, levelHeight);
    Player* player1 = new Player(renderTarget, "assets/Puny-Characters/Character-Base.png", xSpawn, ySpawn, 4, 8, 24, 8, 2, 2);
    randomSpawnCoords(xSpawn, ySpawn, gameObjects, levelWidth, levelWidth);
    Player* player2 = new Player(renderTarget, "assets/Puny-Characters/Character-Base.png", xSpawn, ySpawn, 4, 8, 24, 8, 2, 2);

    gameObjects.push_back(player1);
    gameObjects.push_back(player2);

    for (auto elem : gameObjects) {
        elem->ShrinkIntersectArea();
    }

    while (isRunning) {
        prevTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000;
        while (SDL_PollEvent(&ev) > 0) {
            if (ev.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        keyState = SDL_GetKeyboardState(NULL);

        player1->Update(deltaTime, keyState);
        player2->Update(deltaTime, keyState);

        for (auto& elem : bears) {
            elem->Update(deltaTime);
        }

        for (size_t i = 0; i < gameObjects.size(); i++) {
            if (dynamic_cast<Grass*>(gameObjects.at(i)) == nullptr) {
                if (player1->IntersectsWith(*gameObjects.at(i)) && gameObjects.at(i)->GetID() != player1->GetID()) {
                    player1->Block(deltaTime, keyState);
                }
                if (player2->IntersectsWith(*gameObjects.at(i)) && gameObjects.at(i)->GetID() != player2->GetID()) {
                    player2->Block(deltaTime, keyState);
                }
                for (auto& elem : bears) {
                    if (elem->IntersectsWith(*gameObjects.at(i)) && gameObjects.at(i)->GetID() != elem->GetID()) {
                        elem->Block(deltaTime);
                    }
                }
            }
        }


      
        SDL_RenderClear(renderTarget);
        //Render the spriteSheetTexture on the screen
        SDL_RenderCopy(renderTarget, spriteSheetTexture, NULL, NULL);

        player1->Draw(renderTarget);
        player2->Draw(renderTarget);

        for (auto& elem : bears) {
            elem->Draw(renderTarget);
        }

        SDL_RenderPresent(renderTarget);
    }

    //Cleanup

    SDL_DestroyTexture(spriteSheetTexture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderTarget);

    for (auto elem : gameObjects) {
        elem->~GameObject();
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}

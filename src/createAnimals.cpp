#include <vector>
#include "Bear.h"
#include "GameObject.h"
#include "Header.h"

inline void createBears(SDL_Renderer* renderTarget, std::vector<Bear*>& bears, int levelWidth, int levelHeight, std::vector<GameObject*>& gameObjects) {
    int bearFactor = 921600;
    int numOfBears = levelWidth * levelHeight / bearFactor;
    int xSpawn = 50;
    int ySpawn = 50;

    randomSpawnCoords(xSpawn, ySpawn, gameObjects, levelWidth, levelHeight);

    for (size_t i = 0; i < numOfBears; i++) {
        Bear* newBear = new Bear(renderTarget, "assets/Retro RPG Series - Animal Wildlife/Bear/Bear1_Walking.png.png", xSpawn, ySpawn, 4, 4, 2, 2);
        bears.push_back(newBear);

    }
    for (auto& elem : bears) {
        gameObjects.push_back(elem);
    }
}

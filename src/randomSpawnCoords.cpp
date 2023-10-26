#include <vector>
#include "Header.h"
#include <random>
#include <algorithm>

// Function to check if a point (x, y) is inside any of the rectangles
inline bool isPointInsideObjects(int x, int y, const std::vector<GameObject*>& gameObjects) {
    for (const auto& elem : gameObjects) {
        if (x >= elem->positionRect.x && x <= elem->positionRect.x + elem->positionRect.w &&
            y >= elem->positionRect.y && y <= elem->positionRect.y + elem->positionRect.h &&
            dynamic_cast<Grass*>(elem) == nullptr) {
            return true; // Point is inside a rectangle
        }
    }
    return false; // Point is not inside any rectangle
}

// Function to generate random spawn coordinates
inline void randomSpawnCoords(int& x, int& y, std::vector<GameObject*>& gameObjects, int levelWidth, int levelHeight) {

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distributionX(0, levelWidth - 100);
    std::uniform_int_distribution<int> distributionY(0, levelHeight - 100);

    std::cout << levelWidth << '\n';
    std::cout << levelHeight << '\n';

    int maxAttempts = 100;
    int currentAttempt = 0;

    do {
        x = distributionX(generator);
        y = distributionY(generator);

        currentAttempt++;
    } while (isPointInsideObjects(x, y, gameObjects) && currentAttempt < maxAttempts);

    if (currentAttempt >= maxAttempts) {
        // Handle the case when no valid coordinates are found after a certain number of attempts
        // This could be due to limited space and high object density
        std::cout << "There is no space for new objects\n";
    }
}


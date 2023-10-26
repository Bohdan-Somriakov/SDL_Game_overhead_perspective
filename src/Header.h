#ifndef HEADER_H
#define HEADER_H

#include "SDL.h"
#include "SDL_image.h"

#include "iostream"
#include <vector>

#include "Tree.h"
#include "Grass.h"
#include "Player.h"
#include "Bear.h"

inline SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);

inline void createGrass(SDL_Renderer* renderer, int levelWidth, int levelHeight, std::vector<Grass>& grasses, int widthFactor, int heightFactor, std::vector<GameObject*>& gameObjects);

inline void createForest(SDL_Renderer* renderer, int levelWidth, int levelHeight, std::vector<Tree>& trees, int widthFactor, int heightFactor, std::vector<GameObject*>& gameObjects);

inline bool isPointInsideObjects(int x, int y, const std::vector<GameObject*>& gameObjects);

inline void randomSpawnCoords(int& x, int& y, std::vector<GameObject*>& gameObjects, int levelWidth, int levelHeight);

inline void createBears(SDL_Renderer* renderTarget, std::vector<Bear*>& bear, int levelWidth, int levelHeight, std::vector<GameObject*>& gameObjects);

#endif
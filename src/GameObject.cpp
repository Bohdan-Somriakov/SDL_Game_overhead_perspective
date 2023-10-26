#include "GameObject.h"
#include <cmath>
#include "Player.h"
#include "Bear.h"
int GameObject::giveID = 0;
GameObject::GameObject() : texture(nullptr) {
    ID = giveID;
    giveID++;
}
void GameObject::Draw(SDL_Renderer* renderTarget) {
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}
SDL_Texture* GameObject::GetTexture() {
    return texture;
}
int GameObject::GetOriginX() {
    return positionRect.x + originX;
}
int GameObject::GetOriginY() {
    return positionRect.y + originY;
}
int GameObject::GetRadius() {
    return radius;
}
int GameObject::GetID() {
    return ID;
}
bool GameObject::IntersectsWith(GameObject& otherObject){
    if (sqrt(pow(GetOriginX() - otherObject.GetOriginX(), 2) + pow(GetOriginY() - otherObject.GetOriginY(), 2)) /*+ shrinkIntersectAreaPlayer*/ >= radius + otherObject.GetRadius()) {
        return false;
    }
    else {
        return true;
    }
}

constexpr float shrinkIntersectAreaPlayer = 2.5; 
constexpr float shrinkIntersectAreaTree = 5; 
constexpr float shrinkIntersectAreaBear = 0;

void GameObject::ShrinkIntersectArea() {
    if (dynamic_cast<Player*>(this) != nullptr) {
        radius = (*this).GetRadius() - shrinkIntersectAreaPlayer;
    }
    else if (dynamic_cast<Tree*>(this) != nullptr) {
        radius = (*this).GetRadius() - shrinkIntersectAreaTree;
    }
    else if (dynamic_cast<Bear*>(this) != nullptr) {
        radius = (*this).GetRadius() - shrinkIntersectAreaBear;
    }
}
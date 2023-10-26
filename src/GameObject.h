#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "SDL.h"
#include "SDL_image.h"
#include "iostream"

class GameObject {
protected:
    SDL_Texture* texture;
    SDL_Rect cropRect;
    int originX;
    int originY;
    int radius;
    int ID;
    static int giveID; //increments one time when an object is created
public:
    SDL_Rect positionRect;
    GameObject();
    virtual void Draw(SDL_Renderer* renderTarget);
    //virtual void Update(float delta) = 0;
    //virtual void Draw(SDL_Renderer* renderer) = 0;
    //virtual bool Intersects(GameObject* other) const;
    virtual ~GameObject() {
        std::cout << "Game object was destroyed " << texture << '\n';
        SDL_DestroyTexture(texture);
        texture = nullptr;
    };
    virtual SDL_Texture* GetTexture();
    virtual int GetOriginX();
    virtual int GetOriginY();
    virtual int GetRadius();
    virtual int GetID();
    bool IntersectsWith(GameObject& otherObject);
    void ShrinkIntersectArea(); //in fact, radius
};

#endif
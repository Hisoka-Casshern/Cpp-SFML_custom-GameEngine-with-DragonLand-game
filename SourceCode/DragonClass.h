#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameSettings.h"


class Dragon{
    public:
        //constructor
        Dragon(GameDataShrdPtr CurrentGameData);

        //function to draw the dragon
        void DrawDragon();

        //animate dragon
        void AnimateDragon();

        //update method
        void DragonUpdate(float& deltaTime);

        //method that takes user press
        void UserPressed();

        //method to return the refrence to the sprite for collison check
        const sf::Sprite& GetDragonSprite() const;
    
    private:
        GameDataShrdPtr mCurrentGameData;
        SimpleClock mSimpleClock;
        SimpleClock mDragonMovementSimpleTimer;
        int mDragonState;
        //sprite for dragon, only one, animation will only replace textures
        sf::Sprite mDragonSprite;
        std::vector<sf::Texture> mDragonAnimationFramesVector;
        unsigned int mAnimationCounter = 0;
        //deal with rotation of dragon when pressed
        float mDragonRotation;
        //float for horizontal speed
        float mHorizontalSpeed = 0;

};
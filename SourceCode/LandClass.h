#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
#include "GameSettings.h"

class Land{
    public:
        //constructor
        Land(GameDataShrdPtr CurrentGameData);
        
        //Move land
        void MoveLand(float& DeltaTime, float& HorizontalSpeed);
        
        //function to draw the land
        void DrawLand();
        
        //method to return the refrence to the sprite for collison check
        const std::vector<sf::Sprite>& GetLandSprites() const;

    private:
        GameDataShrdPtr mCurrentGameData;
        //vector to store spawned saws
        std::vector<sf::Sprite> mLandSpritesVector;

};
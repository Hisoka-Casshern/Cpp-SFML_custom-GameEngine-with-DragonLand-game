#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
#include <array>
#include "GameSettings.h"

class Saw{
    public:
        //constructor
        Saw(GameDataShrdPtr CurrentGameData);
        //spawn saws 
        void SpawnDownSaw();
        void SpawnUpSaw();
        void SpawnPlaceholderSaw();
        //function that spawns a scoring tracker saw
        void SpawnSawForScoring();
        //Move them 
        void MoveSaws(float& DeltaTime, float& HorizontalSpeed, bool VerticalMove);
        //function to draw the saw
        void DrawSaws();
        //function to randomize displacement
        void RandomSawDisplacement();
        //method to return the refrence to the sprite for collison check
        const std::vector<sf::Sprite>& GetSawSprites() const;
        //method to return the the scoring sprites
        std::vector<sf::Sprite>& GetScoringSawSprites();
    
    private:
        GameDataShrdPtr mCurrentGameData;
        //four vectors to store spawned saws and their animation images
        //vector of arrays of booleans that will keep track of animation image order
        std::vector<sf::Sprite> mSawSpritesVector1;
        std::vector<sf::Sprite> mSawSpritesVector2;
        std::vector<sf::Sprite> mSawSpritesVector3;
        std::vector<sf::Sprite> mSawSpritesVector4;
        std::vector<std::array<bool,4>> mAnimationPositionImage;
        //x and y Displacement buffers
        int mHaightOfLand;
        int mSawYDisplacement = 0;
        //scoring saws vector
        std::vector<sf::Sprite> mScoringSawsVector;
        
};
#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameSettings.h"

class FlashScreen{
    public:
        //constructor
        FlashScreen(GameDataShrdPtr CurrentGameData);

        //Flash update once metod
        void FlashUpdateOnce(float& deltaTime);

        //draw the flash screen
        void DrawFlashScreen();

    private:
        GameDataShrdPtr mCurrentGameData;
        sf::RectangleShape mRectangleShape;
        bool mIsFlashing;

};

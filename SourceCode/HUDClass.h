#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameSettings.h"

class HUD{
    public:
        //constructor
        HUD(GameDataShrdPtr CurrentGameData);
        //update the current score
        void UpdateCurrentScoreHUD(int& Score);
        //draw the hud
        void DrawHUD();

    private:
        //local game data pointer
        GameDataShrdPtr mCurrentGameData;
        //score text object that will display txt
        sf::Text mScoreText;



};
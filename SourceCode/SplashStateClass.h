#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "StateMachineClass.h"


class SplashState : public State{
    public:
        SplashState(GameDataShrdPtr CurrentGameData);
        //initialization
        void Init();
        //input handler
        void InputHandler();
        //update state
        void StateUpdate(float& deltaTime);
        //draw on screen
        void StateDraw(float& deltaTime);
        
    private:
        //game data buffers
        GameDataShrdPtr mCurrentGameData;
        sf::Sprite mSplashScreenSprite;
        //clock to keep time
        SimpleClock mSimpleClock;
        //intro sound
        sf::Sound mIntroSound;

};
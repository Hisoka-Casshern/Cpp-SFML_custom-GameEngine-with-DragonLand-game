#pragma once

#include "Game.h"
#include "StateMachineClass.h"

class MainMenuState : public State{
    public:
        MainMenuState(GameDataShrdPtr CurrentGameData);
        //initialization
        void Init();
        //input handler
        void InputHandler();
        //update state
        void StateUpdate(float& deltaTime);
        //draw on screen
        void StateDraw(float& deltaTime);
        
    private:
        //game data buffers and check booleans
        GameDataShrdPtr mCurrentGameData;
        sf::Sprite mMainMenuScreenSprite;
        sf::Sprite mMainMenuGameNameSprite;
        sf::Sprite mMainMenuPlayButtonSprite;
        sf::Sprite mMainMenuPlayButtonHoverSprite;
        sf::Sprite mMainMenuQuitButtonSprite;
        sf::Sprite mMainMenuQuitButtonHoverSprite;
        bool mIsHoveringOverPlayButton = false;
        bool mIsHoveringOverQuitButton = false;
        sf::Sound mButtonSoundClick;
        sf::Sound mSoundtrack;
        SimpleClock mSimpleClock;
};
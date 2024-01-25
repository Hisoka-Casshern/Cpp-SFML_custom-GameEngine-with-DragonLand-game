#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "StateMachineClass.h"
#include "GameStateClass.h"


class GameOverState : public State{
    public:
        GameOverState(GameDataShrdPtr CurrentGameData, int& Score);
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
        sf::Sprite mGameBackgroundSprite;
        sf::Sprite mGameOverTitle;
        sf::Sprite mGameScoreBoard;
        sf::Sprite mRetryButton;
        sf::Sprite mRetryButtonHover;
        sf::Sprite mQuitButtonSprite;
        sf::Sprite mQuitButtonHoverSprite;
        bool mIsHoveringOverRetryButton = false;
        bool mIsHoveringOverQuitButton = false;
        //score board elements
        sf::Text mScoreText;
        sf::Text mHighScoreText;
        int mScore;
        int mHighScore;
        sf::Sprite mMedal;
        sf::Sound mScoreBoardTransitionSound;
        sf::Sound mButtonSoundClick;
        sf::Sound mSoundtrack;
        SimpleClock mSimpleCurrentClock;

};
#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "StateMachineClass.h"
#include "CollisionClass.h"
#include "HUDClass.h"
#include "SawClass.h"
#include "LandClass.h"
#include "DragonClass.h"
#include "FlashScreenClass.h"
#include "GameOverStateClass.h"


class GameState : public State{
    public:
        GameState(GameDataShrdPtr CurrentGameData);
        //initialization
        void Init();
        //input handler
        void InputHandler();
        //update state
        void StateUpdate(float& deltaTime);
        //draw on screen
        void StateDraw(float& deltaTime);
  
    private:
        //collision object
        Collision mCollisionCheck;
        //game state based on neum
        int mGameState;
        //game data buffers
        GameDataShrdPtr mCurrentGameData;
        sf::Sprite mGameBackgroundSprite;
        //clock to keep time
        SimpleClock mSimpleClock;
        //HUD object
        HUD* mHUD;
        //create a saw object
        Saw* mSaw;
        //cretae a land object
        Land* mLand;
        //create a dragon
        Dragon* mDragon;
        //flash screen object and settngs
        FlashScreen* mFlashScreen;
        //finally the score
        int mScore;
        //Audio objects 
        sf::Sound mWingFlapSound;
        sf::Sound mGroundHitSound;
        sf::Sound mChainSawHitSound;
        sf::Sound mSoundtrack;
        sf::Sound mWeeeSound;
        int weeeSoundCounter = 0;
        sf::Text mPressToPlay;
        std::string mStandByNotification = "When Ready, Touch Anywhere To Play";
        sf::Sprite mDashButtonReadySprite;
        sf::Sprite mDashButtonNotReadySprite;
        SimpleClock mDashTimer;
        float mCurrentHorizontalSpeed;
        bool mIsDashReady = true;

};
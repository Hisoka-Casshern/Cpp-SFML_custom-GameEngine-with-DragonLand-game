#include "SplashStateClass.h"
#include "GameSettings.h"
#include <iostream>
#include <sstream>
#include "MainMenuStateClass.h"

//function definitions

SplashState::SplashState(GameDataShrdPtr CurrentGameData){
    this->mCurrentGameData = CurrentGameData;
}

void SplashState::Init(){
    //loads the texture from drirectory and sets sprite with given texture
    this->mCurrentGameData->GameAssets.LoadTexture(SplashScreenClosedFilePath, "Splash Screen Closed");
    this->mCurrentGameData->GameAssets.LoadTexture(SplashScreenOpenFilePath, "Splash Screen Open");
    this->mSplashScreenSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Splash Screen Closed"));

    //sound
    this->mCurrentGameData->GameAssets.LoadSound(ThunderSoundFilepath,"Thunder Sound");
    this->mIntroSound.setBuffer(mCurrentGameData->GameAssets.GetSound("Thunder Sound"));
}

void SplashState::InputHandler(){
    //in case if window exit
    //create a listening event
    sf::Event eventListener;
    while(mCurrentGameData->GameWindow.pollEvent(eventListener)){
        if(eventListener.type == sf::Event::Closed) mCurrentGameData->GameWindow.close();
    }
}

void SplashState::StateUpdate(float &deltaTime){
    //keep screen on until specifed time
    //check if intro is playing
    if(mIntroSound.getStatus() != sf::Sound::Playing){
         mIntroSound.play();
    }
    if(mSimpleClock.GetElapsedTimeInSeconds()>((float)SplashScreenTime*(3.f/4.f))){
        this->mSplashScreenSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Splash Screen Open"));
    }
    if(mSimpleClock.GetElapsedTimeInSeconds()>SplashScreenTime){
        mIntroSound.resetBuffer();
        this->mCurrentGameData->GameStateMachine.AddStateOnTheStack(StateUnqPtr(new MainMenuState(this->mCurrentGameData)),true);
    }

}

void SplashState::StateDraw(float &deltaTime){
    //now for the given frame draw the sprite on screen
    //first erase what is already on screen
    this->mCurrentGameData->GameWindow.clear();
    //now draw the sprite in memory
    this->mCurrentGameData->GameWindow.draw(mSplashScreenSprite);
    //display drawn on screen
    this->mCurrentGameData->GameWindow.display();

}

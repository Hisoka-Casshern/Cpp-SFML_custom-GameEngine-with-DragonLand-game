#include "Game.h"
#include "SplashStateClass.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>


//function implementations
Game::Game(int ScreenWidth,int ScreenHeight,std::string ScreenTitle){
    //set seed
    srand(time(NULL));
    //contructor cretes a window firstly
    mGameData->GameWindow.create(sf::VideoMode(ScreenWidth,ScreenHeight),
                ScreenTitle);
    //we add the first state to the state machine
    mGameData->GameStateMachine.AddStateOnTheStack(StateUnqPtr(new SplashState(this->mGameData)));
    //the we run the game
    this->RunGame();
}

void Game::RunGame(){
    //crate buffers 
    float NewTime;
    float TimeBetweenFrames;
    float FrameTimeCounter = 0.f;
    float InterpolatedTime;
    //get current time
    float CurrentTimeSimpleClock = this->mSimpleClock.GetElapsedTimeInSeconds();
    //game loop
    while(this->mGameData->GameWindow.isOpen()){
        //firstly procces any change in states
        this->mGameData->GameStateMachine.ProcessState();
        //get the new time
        float NewTimeSimpleClock = this->mSimpleClock.GetElapsedTimeInSeconds();
        //calculate the time between frames to adjust the correct frame rate speed
        //restrict to change on frames of 0.25s
        //set the current time as new time
        float TimeBetweenFramesSimpleTime = NewTimeSimpleClock - CurrentTimeSimpleClock;
        if(TimeBetweenFramesSimpleTime > 0.25f) TimeBetweenFramesSimpleTime = 0.25f;
        CurrentTimeSimpleClock = NewTimeSimpleClock;
        //increse the counter
        FrameTimeCounter += TimeBetweenFramesSimpleTime;
        while(FrameTimeCounter >= mDeltaTime){
            //handle the input
            this->mGameData->GameStateMachine.GetCurrentState()->InputHandler();
            //update the current active state
            this->mGameData->GameStateMachine.GetCurrentState()->StateUpdate(mDeltaTime);
            //adjust the time frame counter
            FrameTimeCounter -= mDeltaTime;
            //determine the correct delta time for draw method
            InterpolatedTime = FrameTimeCounter/mDeltaTime;
            //call the draw method
            this->mGameData->GameStateMachine.GetCurrentState()->StateDraw(InterpolatedTime);
        }
        
    }
     
}

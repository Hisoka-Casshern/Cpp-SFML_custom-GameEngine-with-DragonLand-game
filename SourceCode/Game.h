#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include "StateMachineClass.h"
#include "InputControllerClass.h"
#include "AssetsControllerClass.h"
#include "SimpleClock.h"

//main classes and game logic

//we create a struct that will hold the game data
struct GameData{
    sf::RenderWindow GameWindow;
    StateMachine GameStateMachine;
    InputController GameInput;
    AssetsController GameAssets;
};

//we create a smart pointer to the GameData
typedef std::shared_ptr<GameData> GameDataShrdPtr;

//now we create a game class
class Game{
    public:
        //c constructor takes width and height of the game window
        //and the name that appears on top of window
        Game(int Width,int Height, std::string ScreenTitle);
    
    private:
        //define frame rate 
        float mFrameRate = 60.f;
        //delta time for consistant gameplay with differnet framerates
        float mDeltaTime = 1.f/mFrameRate;
        //to handle different framerates we use clock
        //sf::Clock mClock;
        SimpleClock mSimpleClock;
        //game data, we allocate and make a smart data pointer
        GameDataShrdPtr mGameData = std::make_shared<GameData>();
        //method that runs the game 
        void RunGame();
};
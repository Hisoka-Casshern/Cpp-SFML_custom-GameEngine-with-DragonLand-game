#include "MainMenuStateClass.h"
#include "GameSettings.h"
#include <iostream>
#include <sstream>
#include "GameStateClass.h"

//function definitions

MainMenuState::MainMenuState(GameDataShrdPtr CurrentGameData){
    this->mCurrentGameData = CurrentGameData;
}

void MainMenuState::Init(){
    //loads the texture from directory and sets sprite with given texture
    //main background
    this->mCurrentGameData->GameAssets.LoadTexture(GameBackgroundFilepath, "Main Screen");
    this->mMainMenuScreenSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Main Screen"));
    
    //title sprite
    this->mCurrentGameData->GameAssets.LoadTexture(GameNameFilepath, "Game Name");
    this->mMainMenuGameNameSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Game Name"));
    
    //play button sprite, set the button position
    //no hover
    this->mCurrentGameData->GameAssets.LoadTexture(PlayButtonFilepath, "Play Button");
    this->mMainMenuPlayButtonSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Play Button"));
    this->mMainMenuPlayButtonSprite.setPosition((ScreenWidth/2)-(this->mMainMenuPlayButtonSprite.getGlobalBounds().width/2),
                                                (ScreenHeight/2)+(this->mMainMenuPlayButtonSprite.getGlobalBounds().width/3));
    //hover
    this->mCurrentGameData->GameAssets.LoadTexture(PlayButtonHoverFilepath, "Play Button Hover");
    this->mMainMenuPlayButtonHoverSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Play Button Hover"));
    this->mMainMenuPlayButtonHoverSprite.setPosition((ScreenWidth/2)-(this->mMainMenuPlayButtonSprite.getGlobalBounds().width/2),
                                                (ScreenHeight/2)+(this->mMainMenuPlayButtonSprite.getGlobalBounds().width/3));
                                    
    //Quit button sprite, set the button position
    //no hover
    this->mCurrentGameData->GameAssets.LoadTexture(QuitButtonFilepath, "Quit Button");
    this->mMainMenuQuitButtonSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Quit Button"));
    this->mMainMenuQuitButtonSprite.setPosition((ScreenWidth/2)-(this->mMainMenuQuitButtonSprite.getGlobalBounds().width/2),
                                                (ScreenHeight/2)+(this->mMainMenuQuitButtonSprite.getGlobalBounds().width));
    //hover
    this->mCurrentGameData->GameAssets.LoadTexture(QuitButtonHoverFilepath, "Quit Button Hover");
    this->mMainMenuQuitButtonHoverSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Quit Button Hover"));
    this->mMainMenuQuitButtonHoverSprite.setPosition((ScreenWidth/2)-(this->mMainMenuQuitButtonHoverSprite.getGlobalBounds().width/2),
                                                (ScreenHeight/2)+(this->mMainMenuQuitButtonHoverSprite.getGlobalBounds().width));

    //buton click sound
    this->mCurrentGameData->GameAssets.LoadSound(ButtonClickFilepath,"Button Click Sound");
    this->mButtonSoundClick.setBuffer(this->mCurrentGameData->GameAssets.GetSound("Button Click Sound"));

    //soundtrack
    this->mCurrentGameData->GameAssets.LoadSound(BackgroundMusic,"Soundtrack");
    this->mSoundtrack.setBuffer(this->mCurrentGameData->GameAssets.GetSound("Soundtrack"));


}
#include <iostream>
void MainMenuState::InputHandler(){
    //create a listening event
    sf::Event eventListener;
    while(mCurrentGameData->GameWindow.pollEvent(eventListener)){
        //check again for close
        if(eventListener.type == sf::Event::Closed) mCurrentGameData->GameWindow.close();

        //hover over play button
        //mouse position and position of play button
        sf::Vector2i MousePosition = sf::Mouse::getPosition(this->mCurrentGameData->GameWindow);
        sf::FloatRect PlayButtonBoundingBox = mMainMenuPlayButtonSprite.getGlobalBounds();
        if(PlayButtonBoundingBox.contains(static_cast<float>(MousePosition.x),static_cast<float>(MousePosition.y)) == true)
            mIsHoveringOverPlayButton = true;
        else mIsHoveringOverPlayButton = false;
        sf::FloatRect QuitButtonBoundingBox = mMainMenuQuitButtonSprite.getGlobalBounds();
        if(QuitButtonBoundingBox.contains(static_cast<float>(MousePosition.x),static_cast<float>(MousePosition.y)) == true)
            mIsHoveringOverQuitButton = true;
        else mIsHoveringOverQuitButton = false;        

        //check if button pressed
        float WaitButtonTime = 0.2f;
        if(this->mCurrentGameData->GameInput.IsSpriteClicked(this->mCurrentGameData->GameWindow,
                                                    mMainMenuPlayButtonSprite, sf::Mouse::Left) == true){
            mSoundtrack.resetBuffer();
            mButtonSoundClick.play();
            mSimpleClock.Restart();
            while (WaitButtonTime > mSimpleClock.GetElapsedTimeInSeconds()){}
            mButtonSoundClick.resetBuffer();
            this->mCurrentGameData->GameStateMachine.AddStateOnTheStack(StateUnqPtr(new GameState(this->mCurrentGameData)),true);                                  
        }

        if(this->mCurrentGameData->GameInput.IsSpriteClicked(this->mCurrentGameData->GameWindow,
                                                    mMainMenuQuitButtonSprite, sf::Mouse::Left) == true){
            mSoundtrack.resetBuffer();
            mButtonSoundClick.play();
            mCurrentGameData->GameWindow.close();                                 
        }
        
    }
}

void MainMenuState::StateUpdate(float &deltaTime){
    //check if music is playing
    if(mSoundtrack.getStatus() != sf::Sound::Playing){
         mSoundtrack.play();
    }
}

void MainMenuState::StateDraw(float &deltaTime){
    //now for the given frame draw the sprite on screen
    //first erase what is already on screen
    this->mCurrentGameData->GameWindow.clear();
    //now draw the sprites in memory
    this->mCurrentGameData->GameWindow.draw(mMainMenuScreenSprite);
    this->mCurrentGameData->GameWindow.draw(mMainMenuGameNameSprite);

    if(mIsHoveringOverPlayButton == false)
        this->mCurrentGameData->GameWindow.draw(mMainMenuPlayButtonSprite);
    else
        this->mCurrentGameData->GameWindow.draw(mMainMenuPlayButtonHoverSprite);

    if(mIsHoveringOverQuitButton == false)
        this->mCurrentGameData->GameWindow.draw(mMainMenuQuitButtonSprite);
    else
        this->mCurrentGameData->GameWindow.draw(mMainMenuQuitButtonHoverSprite);
    //display drawn on screen
    this->mCurrentGameData->GameWindow.display();

}

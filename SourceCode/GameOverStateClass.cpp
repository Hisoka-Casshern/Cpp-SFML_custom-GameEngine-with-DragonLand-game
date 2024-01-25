#include "GameOverStateClass.h"
#include "GameSettings.h"
#include <iostream>
#include <sstream>
#include <fstream>

//function definitions

GameOverState::GameOverState(GameDataShrdPtr CurrentGameData, int& Score){
    this->mCurrentGameData = CurrentGameData;
    mScore = Score;
}

void GameOverState::Init(){
    //load the value of high score from file and check if opened
    
    std::ifstream ReadFile;
    ReadFile.open(HighScoreTxtFilepath);
    if(ReadFile.is_open()){
        ReadFile >> mHighScore;
        //close the file
        ReadFile.close();
    }
    //open stream to write high score
    std::ofstream WriteFile;
    WriteFile.open(HighScoreTxtFilepath);
    if(WriteFile.is_open()){
        if(mHighScore < mScore)
            mHighScore = mScore;
        WriteFile << mHighScore;          
        WriteFile.close();
    }
    

    //loads the texture from drirectory and sets sprite with given texture
    //load 
    this->mCurrentGameData->GameAssets.LoadTexture(GameBackgroundFilepath, "GameOver Background");
    this->mCurrentGameData->GameAssets.LoadTexture(GameOverTitleFilepath,"Game Over Title");
    this->mCurrentGameData->GameAssets.LoadTexture(GameOverScoreBoardFilepath,"Game Over Score Board");
    //set
    this->mGameBackgroundSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("GameOver Background"));
    this->mGameScoreBoard.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Game Over Score Board"));
    this->mGameScoreBoard.setPosition((mCurrentGameData->GameWindow.getSize().x/2.f)-(mGameScoreBoard.getGlobalBounds().width/2.f),
                                      (mCurrentGameData->GameWindow.getSize().x/2.f)-(mGameScoreBoard.getGlobalBounds().height/2.f));
    this->mGameOverTitle.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Game Over Title"));
    this->mGameOverTitle.setPosition((mCurrentGameData->GameWindow.getSize().x/2.f)-(mGameOverTitle.getGlobalBounds().width/2.f),
                                       mGameScoreBoard.getPosition().y-(mGameOverTitle.getGlobalBounds().height*1.2));
    
    //retry button sprite, set the button position
    //no hover
    this->mCurrentGameData->GameAssets.LoadTexture(RetryButtonFilepath, "Retry Button");
    this->mRetryButton.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Retry Button"));
    this->mRetryButton.setPosition((ScreenWidth/2)-(this->mRetryButton.getGlobalBounds().width/2),
                                    (mGameScoreBoard.getPosition().y +mGameScoreBoard.getGlobalBounds().height)+
                                    (mRetryButton.getGlobalBounds().height*0.2));
    //hover
    this->mCurrentGameData->GameAssets.LoadTexture(RetryButtonHoverFilepath, "Retry Button Hover");
    this->mRetryButtonHover.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Retry Button Hover"));
    this->mRetryButtonHover.setPosition((ScreenWidth/2)-(this->mRetryButton.getGlobalBounds().width/2),
                                    (mGameScoreBoard.getPosition().y +mGameScoreBoard.getGlobalBounds().height)+
                                    (mRetryButtonHover.getGlobalBounds().height*0.2));

    //Quit button sprite, set the button position
    //no hover
    this->mCurrentGameData->GameAssets.LoadTexture(QuitButtonFilepath, "Quit Button");
    this->mQuitButtonSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Quit Button"));
    this->mQuitButtonSprite.setPosition((ScreenWidth/2)-(this->mQuitButtonSprite.getGlobalBounds().width/2),
                                                (ScreenHeight/2)+(this->mQuitButtonSprite.getGlobalBounds().width/1.2));
    //hover
    this->mCurrentGameData->GameAssets.LoadTexture(QuitButtonHoverFilepath, "Quit Button Hover");
    this->mQuitButtonHoverSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Quit Button Hover"));
    this->mQuitButtonHoverSprite.setPosition((ScreenWidth/2)-(this->mQuitButtonHoverSprite.getGlobalBounds().width/2),
                                                (ScreenHeight/2)+(this->mQuitButtonHoverSprite.getGlobalBounds().width/1.2));


    //score text
    mScoreText.setFont(mCurrentGameData->GameAssets.GetFont("Thick Font"));
    mScoreText.setString(std::to_string(mScore));
    mScoreText.setCharacterSize(ScoreBoardFontSize);
    mScoreText.setFillColor(ScoreBoardFontColor);
    mScoreText.setOrigin(mScoreText.getGlobalBounds().width/2.f,mScoreText.getGlobalBounds().height/2.f);
    mScoreText.setPosition(mCurrentGameData->GameWindow.getSize().x/10*3.2,
                            mCurrentGameData->GameWindow.getSize().y/2.4);
    //highscore text
    mHighScoreText.setFont(mCurrentGameData->GameAssets.GetFont("Thick Font"));
    mHighScoreText.setString(std::to_string(mHighScore));
    mHighScoreText.setCharacterSize(ScoreBoardFontSize);
    mHighScoreText.setFillColor(ScoreBoardFontColor);
    mHighScoreText.setOrigin(mHighScoreText.getGlobalBounds().width/2.f,mHighScoreText.getGlobalBounds().height/2.f);
    mHighScoreText.setPosition(mCurrentGameData->GameWindow.getSize().x/10*6.9 ,
                            mCurrentGameData->GameWindow.getSize().y/2.4);

    //medals
    this->mCurrentGameData->GameAssets.LoadTexture(BronzeMedalFilepath, "Bronze Medal");
    this->mCurrentGameData->GameAssets.LoadTexture(SilverMedalFilepath, "Silver Medal");
    this->mCurrentGameData->GameAssets.LoadTexture(GoldMedalFilepath, "Gold Medal");
    this->mMedal.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Bronze Medal"));
    this->mMedal.setPosition(mCurrentGameData->GameWindow.getSize().x/10*4.3,
                            mCurrentGameData->GameWindow.getSize().y/2.95);


    //sound load and play instantly
    this->mCurrentGameData->GameAssets.LoadSound(ScoreBoardScreenSoundTransition,"Score Board Transition Sound");
    this->mScoreBoardTransitionSound.setBuffer(this->mCurrentGameData->GameAssets.GetSound("Score Board Transition Sound"));    
    this->mScoreBoardTransitionSound.play();

    //buton click sound
    this->mCurrentGameData->GameAssets.LoadSound(ButtonClickFilepath,"Button Click Sound");
    this->mButtonSoundClick.setBuffer(this->mCurrentGameData->GameAssets.GetSound("Button Click Sound"));
    
    //soundtrack
    this->mCurrentGameData->GameAssets.LoadSound(BackgroundMusic,"Soundtrack");
    this->mSoundtrack.setBuffer(this->mCurrentGameData->GameAssets.GetSound("Soundtrack"));
}

void GameOverState::InputHandler(){
    //in case if window exit
    //create a listening event
    sf::Event eventListener;
    while(mCurrentGameData->GameWindow.pollEvent(eventListener)){
        if(eventListener.type == sf::Event::Closed) mCurrentGameData->GameWindow.close();
        //retry button
        //hover over retry button
        //mouse position and position of play button
        sf::Vector2i MousePosition = sf::Mouse::getPosition(this->mCurrentGameData->GameWindow);
        sf::FloatRect PlayButtonBoundingBox = mRetryButton.getGlobalBounds();
        if(PlayButtonBoundingBox.contains(static_cast<float>(MousePosition.x),static_cast<float>(MousePosition.y)) == true)
            mIsHoveringOverRetryButton = true;
        else mIsHoveringOverRetryButton = false;
        sf::FloatRect QuitButtonBoundingBox = mQuitButtonSprite.getGlobalBounds();
        if(QuitButtonBoundingBox.contains(static_cast<float>(MousePosition.x),static_cast<float>(MousePosition.y)) == true)
            mIsHoveringOverQuitButton = true;
        else mIsHoveringOverQuitButton = false;

        //check if button pressed
        float WaitButtonTime = 0.2f;
        if(this->mCurrentGameData->GameInput.IsSpriteClicked(this->mCurrentGameData->GameWindow,
                                                    mRetryButton, sf::Mouse::Left) == true){
            //clear sound buffer
            mSoundtrack.resetBuffer();
            mButtonSoundClick.play();
            mSimpleCurrentClock.Restart();
            while (WaitButtonTime > mSimpleCurrentClock.GetElapsedTimeInSeconds()){}
            mButtonSoundClick.resetBuffer();
            mScoreBoardTransitionSound.resetBuffer();
            this->mCurrentGameData->GameStateMachine.AddStateOnTheStack(StateUnqPtr(new GameState(this->mCurrentGameData)),true);                                  
        }
        if(this->mCurrentGameData->GameInput.IsSpriteClicked(this->mCurrentGameData->GameWindow,
                                                    mQuitButtonSprite, sf::Mouse::Left) == true){
            //clear sound buffer
            mSoundtrack.resetBuffer();
            mButtonSoundClick.play();
            //quit
            mCurrentGameData->GameWindow.close();                                
        }
    }
}

void GameOverState::StateUpdate(float &deltaTime){
    //check if music is playing
    if(mSoundtrack.getStatus() != sf::Sound::Playing){
         mSoundtrack.play();
    }
}

void GameOverState::StateDraw(float &deltaTime){
    //now for the given frame draw the sprite on screen
    //first erase what is already on screen
    this->mCurrentGameData->GameWindow.clear();
    //now draw the sprites in memory
    this->mCurrentGameData->GameWindow.draw(mGameBackgroundSprite);
    this->mCurrentGameData->GameWindow.draw(mGameScoreBoard);
    this->mCurrentGameData->GameWindow.draw(mGameOverTitle);
    this->mCurrentGameData->GameWindow.draw(mGameScoreBoard);

    if(mIsHoveringOverRetryButton == false)
        this->mCurrentGameData->GameWindow.draw(mRetryButton);
    else this->mCurrentGameData->GameWindow.draw(mRetryButtonHover);
    if(mIsHoveringOverQuitButton == false)
        this->mCurrentGameData->GameWindow.draw(mQuitButtonSprite);
    else this->mCurrentGameData->GameWindow.draw(mQuitButtonHoverSprite);

    this->mCurrentGameData->GameWindow.draw(mScoreText);
    this->mCurrentGameData->GameWindow.draw(mHighScoreText);

    if(mScore>=ScoreToGetBronzeMedal && mScore<ScoreToGetSilverMedal)
        this->mCurrentGameData->GameWindow.draw(mMedal);
    else if(mScore>=ScoreToGetSilverMedal && mScore<ScoreToGetGoldMedal){
        mMedal.setTexture(mCurrentGameData->GameAssets.GetTexture("Silver Medal"));
        this->mCurrentGameData->GameWindow.draw(mMedal);
    }
    else if(mScore>=ScoreToGetGoldMedal){
        mMedal.setTexture(mCurrentGameData->GameAssets.GetTexture("Gold Medal"));
        this->mCurrentGameData->GameWindow.draw(mMedal);
    }

    //display drawn on screen
    this->mCurrentGameData->GameWindow.display();

}


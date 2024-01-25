#include "GameStateClass.h"
#include "GameSettings.h"
#include <iostream>
#include <sstream>

//function definitions

GameState::GameState(GameDataShrdPtr CurrentGameData){
    this->mCurrentGameData = CurrentGameData;
}

void GameState::Init(){
    //get original horizontal speed
    this->mCurrentHorizontalSpeed = DefaultHorizontalSpeed;
    //dash
    this->mIsDashReady = true;

    //loads the texture from drirectory and sets sprite with given texture
    this->mCurrentGameData->GameAssets.LoadTexture(GameBackgroundFilepath, "Game Background");
    this->mGameBackgroundSprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Game Background"));

    //HUD
    this->mCurrentGameData->GameAssets.LoadFont(ThickFontFilepath,"Thick Font");
    //construct the object
    mHUD = new HUD(mCurrentGameData);

    //land 
    this->mCurrentGameData->GameAssets.LoadTexture(LandFilepath, "Land");
    //create a land object
    mLand = new Land(mCurrentGameData);    
    
    //saw , up and down, all four images for each
    //up saw images
    this->mCurrentGameData->GameAssets.LoadTexture(SawUp1Filepath, "Saw UP1");
    this->mCurrentGameData->GameAssets.LoadTexture(SawUp2Filepath, "Saw UP2");
    this->mCurrentGameData->GameAssets.LoadTexture(SawUp3Filepath, "Saw UP3");
    this->mCurrentGameData->GameAssets.LoadTexture(SawUp4Filepath, "Saw UP4");
    //down saw images
    this->mCurrentGameData->GameAssets.LoadTexture(SawDown1FilePath, "Saw DOWN1");
    this->mCurrentGameData->GameAssets.LoadTexture(SawDown2FilePath, "Saw DOWN2");
    this->mCurrentGameData->GameAssets.LoadTexture(SawDown3FilePath, "Saw DOWN3");
    this->mCurrentGameData->GameAssets.LoadTexture(SawDown4FilePath, "Saw DOWN4");
    //scoring saw
    this->mCurrentGameData->GameAssets.LoadTexture(ScoringSawFilepath, "Scoring Saw");
    //create a saw object buffer
    mSaw = new Saw(mCurrentGameData);

    //dragon textures
    this->mCurrentGameData->GameAssets.LoadTexture(DargonFrame1Filepath,"Dragon Frame 1");
    this->mCurrentGameData->GameAssets.LoadTexture(DargonFrame2Filepath,"Dragon Frame 2");
    this->mCurrentGameData->GameAssets.LoadTexture(DargonFrame3Filepath,"Dragon Frame 3");
    this->mCurrentGameData->GameAssets.LoadTexture(DargonFrame4Filepath,"Dragon Frame 4");
    this->mCurrentGameData->GameAssets.LoadTexture(DargonFrame5Filepath,"Dragon Frame 5");
    this->mCurrentGameData->GameAssets.LoadTexture(DargonFrame6Filepath,"Dragon Frame 6");
    this->mCurrentGameData->GameAssets.LoadTexture(DargonFrame7Filepath,"Dragon Frame 7");
    this->mCurrentGameData->GameAssets.LoadTexture(DargonFrame8Filepath,"Dragon Frame 8");
    //create a dragon object
    mDragon = new Dragon(mCurrentGameData);

    //load sounds
    this->mCurrentGameData->GameAssets.LoadSound(WingFlapFilepath,"Wing Flap Sound");
    this->mWingFlapSound.setBuffer(this->mCurrentGameData->GameAssets.GetSound("Wing Flap Sound"));
    
    this->mCurrentGameData->GameAssets.LoadSound(GroundHitFilepath,"Ground Hit Sound");
    this->mGroundHitSound.setBuffer(this->mCurrentGameData->GameAssets.GetSound("Ground Hit Sound"));
    
    this->mCurrentGameData->GameAssets.LoadSound(ChainSawHitFilepath,"Saw Hit Sound");
    this->mChainSawHitSound.setBuffer(this->mCurrentGameData->GameAssets.GetSound("Saw Hit Sound"));
    
    this->mCurrentGameData->GameAssets.LoadSound(WeeeSoundFilepath,"weee");
    this->mWeeeSound.setBuffer(this->mCurrentGameData->GameAssets.GetSound("weee"));
    
    this->mCurrentGameData->GameAssets.LoadSound(BackgroundMusic,"Soundtrack");
    this->mSoundtrack.setBuffer(this->mCurrentGameData->GameAssets.GetSound("Soundtrack"));


    //text that is shown while in standby
    mPressToPlay.setFont(mCurrentGameData->GameAssets.GetFont("Thick Font"));
    mPressToPlay.setString(mStandByNotification);
    mPressToPlay.setCharacterSize(StandByNotificationSize);
    mPressToPlay.setFillColor(ScoreBoardFontColor);
    mPressToPlay.setOrigin(mPressToPlay.getGlobalBounds().width/2.f,mPressToPlay.getGlobalBounds().height/2.f);
    mPressToPlay.setPosition(mCurrentGameData->GameWindow.getSize().x/2,
                            mCurrentGameData->GameWindow.getSize().y/6.5);


    /*
    //Dash Button
    //ready
    this->mCurrentGameData->GameAssets.LoadTexture(DashReadyButtonFilepath, "Dash Ready Button");
    this->mDashButtonReadySprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Dash Ready Button"));
    this->mDashButtonReadySprite.setPosition((ScreenWidth/2)-(this->mDashButtonReadySprite.getGlobalBounds().width/2),
                                                (ScreenHeight/2)+(this->mDashButtonReadySprite.getGlobalBounds().width));
    //pressed
    this->mCurrentGameData->GameAssets.LoadTexture(DashNotReadyButtonFilepath, "Dash Not Ready Button");
    this->mDashButtonNotReadySprite.setTexture(this->mCurrentGameData->GameAssets.GetTexture("Dash Not Ready Button"));
    this->mDashButtonNotReadySprite.setPosition((ScreenWidth/2)-(this->mDashButtonNotReadySprite.getGlobalBounds().width/2),
                                                (ScreenHeight/2)+(this->mDashButtonNotReadySprite.getGlobalBounds().width));
    */

    //set the state to standby
    mGameState = GameStates::eStandby;

    //flash screen
    mFlashScreen = new FlashScreen(mCurrentGameData);

    //set score to zero
    mScore = 0;
}

void GameState::InputHandler(){
    //create a listening event
    sf::Event eventListener;
    while(mCurrentGameData->GameWindow.pollEvent(eventListener)){
        //listen to close of window        
        if(eventListener.type == sf::Event::Closed) mCurrentGameData->GameWindow.close(); 

        //listen to player input, if clicked anywhere
        if(mCurrentGameData->GameInput.IsSpriteClicked(this->mCurrentGameData->GameWindow,mGameBackgroundSprite,sf::Mouse::Left)){
                //call the pressed method from dragon class, only if not game over state
                if(mGameState != GameStates::eGameOver){
                    mGameState = GameStates::ePlaying;
                    mDragon->UserPressed();
                    mWingFlapSound.play();
                    weeeSoundCounter++;
                    if(weeeSoundCounter==4){
                        //mWeeeSound.play();
                        weeeSoundCounter = 0;
                    }
                    
                } 
        }
        /*
        if(mCurrentGameData->GameInput.IsSpriteClicked(this->mCurrentGameData->GameWindow,mDashButtonReadySprite,sf::Mouse::Left)){
                //dash, only if not game over state
                if(mGameState != GameStates::eGameOver){
                    float elapsedTime = mDashTimer.GetElapsedTimeInSeconds();
                    if(elapsedTime >DashTimeout) mIsDashReady = true; 
                    if(mIsDashReady == true){
                        mCurrentHorizontalSpeed += DashSpeed;                   
                        mDashTimer.Restart();                    
                        mIsDashReady = false;
                    }                                 
                }
        }
        else mCurrentHorizontalSpeed = DefaultHorizontalSpeed;         
        */
    }
}

void GameState::StateUpdate(float &deltaTime){

    //if dash ready reset its clock
    //if(mIsDashReady) mDashTimer.Restart();

    //check if music is playing
    if(mSoundtrack.getStatus() != sf::Sound::Playing){
         mSoundtrack.play();
    }
    
    //move land
    if(mGameState != GameStates::eGameOver) mLand->MoveLand(deltaTime,mCurrentHorizontalSpeed);

    //animate dragon 
    if(mGameState != GameStates::eGameOver) mDragon->AnimateDragon();

    //while playing
    if(mGameState == GameStates::ePlaying){
        //move the saws
        mSaw->MoveSaws(deltaTime,mCurrentHorizontalSpeed,false);

        //spawn pipes
        if(mSimpleClock.GetElapsedTimeInSeconds() > SawSpawnFrequency/(mCurrentHorizontalSpeed/DefaultHorizontalSpeed)){
            mSaw->RandomSawDisplacement();
            mSaw->SpawnPlaceholderSaw();
            mSaw->SpawnDownSaw();
            mSaw->SpawnUpSaw();
            mSaw->SpawnSawForScoring();
            //reset internal clock
            mSimpleClock.Restart();
        }

        //dragon update its status
        mDragon->DragonUpdate(deltaTime);

        //check for collision with land
        std::vector<sf::Sprite> LandSprites = mLand->GetLandSprites();
        for(unsigned int idx = 0; idx < LandSprites.size(); idx++){
            if(mCollisionCheck.IsCollided(mDragon->GetDragonSprite(),LandSprites.at(idx),0.75f,0.75f,1.f,1.f) == true){
                if(mScore > 0){
                    mScore-=1;
                    mHUD->UpdateCurrentScoreHUD(mScore);
                }
                mGroundHitSound.play();
                mGameState = GameStates::eGameOver;
                //restart clock to chek for game over screen
                mSimpleClock.Restart();

            }
        }

        //check for collision with saws
        std::vector<sf::Sprite> SawSprites = mSaw->GetSawSprites();
        for(unsigned int idx = 0; idx < SawSprites.size(); idx++){
            if(mCollisionCheck.IsCollided(mDragon->GetDragonSprite(),SawSprites.at(idx),0.6f,0.5f,.8f,1.f) == true){
                if(mScore > 0){
                    mChainSawHitSound.play();
                    mScore-=1;
                    mHUD->UpdateCurrentScoreHUD(mScore);
                }
                //restart clock to chek for game over screen
                mSimpleClock.Restart();
                mGameState = GameStates::eGameOver;
            }    
        }

        //check for scoring
        std::vector<sf::Sprite>& ScoringSawSprites = mSaw->GetScoringSawSprites();
        bool collided = false;
        unsigned int PositionInsideVector = 0;
        for(unsigned int idx = 0; idx < ScoringSawSprites.size(); idx++){
            if(mCollisionCheck.IsCollided(mDragon->GetDragonSprite(),ScoringSawSprites.at(idx),0.6f,0.5f,.8f,1.f) ==  true)
                //increase the score
                collided = true;
                PositionInsideVector = idx;
                break;
        }
        if(collided == true){
            mScore++;
            mHUD->UpdateCurrentScoreHUD(mScore);
            ScoringSawSprites.erase(ScoringSawSprites.begin()+PositionInsideVector);
        }         
    }

    //check if game state is game over and flash the screen
    if(mGameState == GameStates::eGameOver){
        mFlashScreen->FlashUpdateOnce(deltaTime);
        //now check for time for game over screen
        if(mSimpleClock.GetElapsedTimeInSeconds() > TimeBeforeGameOver){
            //reset sound buffers
            mWingFlapSound.resetBuffer();
            mGroundHitSound.resetBuffer();
            mChainSawHitSound.resetBuffer();
            mSoundtrack.resetBuffer();
            mWeeeSound.resetBuffer();
            this->mCurrentGameData->GameStateMachine.AddStateOnTheStack(  
                    StateUnqPtr(new GameOverState(mCurrentGameData, this->mScore)),true);
        }
    }
}

void GameState::StateDraw(float &deltaTime){
    //now for the given frame draw the sprite on screen
    //first erase what is already on screen
    this->mCurrentGameData->GameWindow.clear();
    //now draw the sprite in memory
    this->mCurrentGameData->GameWindow.draw(mGameBackgroundSprite);
    mSaw->DrawSaws();
    mLand->DrawLand();
    mDragon->DrawDragon();
    mHUD->DrawHUD();
    this->mCurrentGameData->GameWindow.draw(mDashButtonReadySprite);
    if(mGameState == GameStates::eStandby) mCurrentGameData->GameWindow.draw(mPressToPlay);
    //draw flash with zero alpha 
    mFlashScreen->DrawFlashScreen();
    //display drawn on screen
    this->mCurrentGameData->GameWindow.display();
}


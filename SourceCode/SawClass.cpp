#include "SawClass.h"
#include <random>
#include <iostream>

//function definitions
Saw::Saw(GameDataShrdPtr CurrentGameData){
    this->mCurrentGameData = CurrentGameData;
    this->mHaightOfLand = CurrentGameData->GameAssets.GetTexture("Land").getSize().y;
}

void Saw::SpawnDownSaw(){
    //create up saws
    sf::Sprite DownSaw1(this->mCurrentGameData->GameAssets.GetTexture("Saw UP1"));
    sf::Sprite DownSaw2(this->mCurrentGameData->GameAssets.GetTexture("Saw UP2"));
    sf::Sprite DownSaw3(this->mCurrentGameData->GameAssets.GetTexture("Saw UP3"));
    sf::Sprite DownSaw4(this->mCurrentGameData->GameAssets.GetTexture("Saw UP4"));

    //set positions
    DownSaw1.setPosition(this->mCurrentGameData->GameWindow.getSize().x,
                        this->mCurrentGameData->GameWindow.getSize().y-DownSaw1.getGlobalBounds().height
                        -mSawYDisplacement);
    
    //put it inside vector buffer
    mSawSpritesVector1.push_back(DownSaw1);
    mSawSpritesVector2.push_back(DownSaw2);
    mSawSpritesVector3.push_back(DownSaw3);
    mSawSpritesVector4.push_back(DownSaw4);

    //append the animation track bool buffer
    mAnimationPositionImage.push_back({true,false,false,false});
}

void Saw::SpawnUpSaw(){
    //create a saw
    sf::Sprite UpSaw1(this->mCurrentGameData->GameAssets.GetTexture("Saw DOWN1"));
    sf::Sprite UpSaw2(this->mCurrentGameData->GameAssets.GetTexture("Saw DOWN2"));
    sf::Sprite UpSaw3(this->mCurrentGameData->GameAssets.GetTexture("Saw DOWN3"));
    sf::Sprite UpSaw4(this->mCurrentGameData->GameAssets.GetTexture("Saw DOWN4"));
    
    //set its position
    UpSaw1.setPosition(this->mCurrentGameData->GameWindow.getSize().x,-mSawYDisplacement);
    
    //put it inside vector buffer with each image of animation
    mSawSpritesVector1.push_back(UpSaw1);
    mSawSpritesVector2.push_back(UpSaw2);
    mSawSpritesVector3.push_back(UpSaw3);
    mSawSpritesVector4.push_back(UpSaw4);

    //append the animation track bool buffer
    mAnimationPositionImage.push_back({true,false,false,false});
}

void Saw::SpawnPlaceholderSaw(){
    //create a saw
    sf::Sprite PlaceholderSaw1(this->mCurrentGameData->GameAssets.GetTexture("Saw DOWN1"));
    sf::Sprite PlaceholderSaw2(this->mCurrentGameData->GameAssets.GetTexture("Saw DOWN1"));
    sf::Sprite PlaceholderSaw3(this->mCurrentGameData->GameAssets.GetTexture("Saw DOWN1"));
    sf::Sprite PlaceholderSaw4(this->mCurrentGameData->GameAssets.GetTexture("Saw DOWN1"));
    
    //set its position
    PlaceholderSaw1.setPosition(this->mCurrentGameData->GameWindow.getSize().x,-mSawYDisplacement);
    
    //make the placeholder from some inpput sprite saw
    PlaceholderSaw1.setColor(sf::Color(0,0,0,0));
    PlaceholderSaw2.setColor(sf::Color(0,0,0,0));
    PlaceholderSaw3.setColor(sf::Color(0,0,0,0));
    PlaceholderSaw4.setColor(sf::Color(0,0,0,0));

    //put it inside vector buffer
    mSawSpritesVector1.push_back(PlaceholderSaw1);
    mSawSpritesVector2.push_back(PlaceholderSaw2);
    mSawSpritesVector3.push_back(PlaceholderSaw3);
    mSawSpritesVector4.push_back(PlaceholderSaw4);

    //append the animation track bool buffer
    mAnimationPositionImage.push_back({true,false,false,false});
    
}

void Saw::SpawnSawForScoring(){
    //create a scoring saw
    sf::Sprite ScoringSaw(this->mCurrentGameData->GameAssets.GetTexture("Scoring Saw"));
    
    //set its position
    ScoringSaw.setPosition(this->mCurrentGameData->GameWindow.getSize().x,0);

    //fill the buffer vector
    mScoringSawsVector.push_back(ScoringSaw);
}

void Saw::MoveSaws(float& DeltaTime, float& HorizontalSpeed, bool VerticalMove){
    //loop over size of vector
    for(unsigned short int idx = 0; idx < mSawSpritesVector1.size(); idx++){
        //check if any sprite is off the left side of screen and remove it from memory
        if(mSawSpritesVector1.at(idx).getPosition().x < (0-mSawSpritesVector1.at(idx).getGlobalBounds().width)){
            mSawSpritesVector1.erase(mSawSpritesVector1.begin()+idx);
            mSawSpritesVector2.erase(mSawSpritesVector2.begin()+idx);
            mSawSpritesVector3.erase(mSawSpritesVector3.begin()+idx);
            mSawSpritesVector4.erase(mSawSpritesVector4.begin()+idx);
            mAnimationPositionImage.erase(mAnimationPositionImage.begin()+idx);
            continue;
        }

       //multiply the deltatime and move, also randomly move pixel up or down
       float horizontalDisplacement = -HorizontalSpeed * DeltaTime;
       //Random vertical
       int verticalDisplacement;
       std::random_device randomDevice;
       std::mt19937 gen(randomDevice());
       std::uniform_real_distribution<> distribution(0, 1);
       float randomNumber = distribution(gen);
       if(randomNumber > 0.6) verticalDisplacement = 1;
       else if (randomNumber < 0.3) verticalDisplacement = -1;
       else verticalDisplacement = 0;
       //SawSpritesVector.at(idx).move(horizontalDisplacement,verticalDisplacement);
       mSawSpritesVector1.at(idx).move(horizontalDisplacement,0);
    }

    //move scoring tracker saw
    for(unsigned short int idx = 0; idx < mScoringSawsVector.size(); idx++){
        //check if any sprite is off the left side of screen and remove it from memory
        if(mScoringSawsVector.at(idx).getPosition().x < (0-mScoringSawsVector.at(idx).getGlobalBounds().width)){
            mScoringSawsVector.erase(mScoringSawsVector.begin()+idx);
            continue;
        }

       //multiply the deltatime and move, also randomly move pixel up or down
       float horizontalDisplacement = -HorizontalSpeed * DeltaTime;
       //SawSpritesVector.at(idx).move(horizontalDisplacement,verticalDisplacement);
       mScoringSawsVector.at(idx).move(horizontalDisplacement,0);
    }
}

void Saw::DrawSaws(){
    //loop over size of vector and draw each pipe inside
    for(unsigned short int i = 0; i < mSawSpritesVector1.size(); i++){
        //current saw position
        sf::Vector2f CurrentPosition = mSawSpritesVector1.at(i).getPosition();
        //check which animation image to render and render it
        for(unsigned short int j = 0; j < 4; j++){
            if(mAnimationPositionImage.at(i)[j] == true){
                switch(j){
                    case 0:
                        this->mCurrentGameData->GameWindow.draw(mSawSpritesVector1.at(i));
                        this->mAnimationPositionImage.at(i) = {false,true,false,false};
                        break;
                    case 1:
                        mSawSpritesVector2.at(i).setPosition(CurrentPosition.x,CurrentPosition.y);
                        this->mCurrentGameData->GameWindow.draw(mSawSpritesVector2.at(i));
                        this->mAnimationPositionImage.at(i) = {false,false,true,false};
                        break;
                    case 2:
                        mSawSpritesVector3.at(i).setPosition(CurrentPosition.x,CurrentPosition.y);
                        this->mCurrentGameData->GameWindow.draw(mSawSpritesVector3.at(i));
                        this->mAnimationPositionImage.at(i) = {false,false,false,true};
                        break;
                    case 3:
                        mSawSpritesVector4.at(i).setPosition(CurrentPosition.x,CurrentPosition.y);
                        this->mCurrentGameData->GameWindow.draw(mSawSpritesVector4.at(i));                                                
                        this->mAnimationPositionImage.at(i) = {true,false,false,false};
                        break;
                }
                break;
            }
        }
    }
    
}

void Saw::RandomSawDisplacement(){
    //randomize between 0 and height of the land
    this->mSawYDisplacement = rand() % (mHaightOfLand +1);
}

const std::vector<sf::Sprite>& Saw::GetSawSprites() const{
    return mSawSpritesVector1;
}

std::vector<sf::Sprite>& Saw::GetScoringSawSprites(){
    return mScoringSawsVector;
}

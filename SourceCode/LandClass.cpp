#include "LandClass.h"
#include "GameSettings.h"

Land::Land(GameDataShrdPtr CurrentGameData){
    //assign
    this->mCurrentGameData = CurrentGameData;
    //create two sprite for land
    sf::Sprite LandSprite1(mCurrentGameData->GameAssets.GetTexture("Land"));
    sf::Sprite LandSprite2(mCurrentGameData->GameAssets.GetTexture("Land"));
    //set postion of both one starting of screen one offscreen
    LandSprite1.setPosition(0,mCurrentGameData->GameWindow.getSize().y -
                                        LandSprite1.getGlobalBounds().height);
    LandSprite2.setPosition(LandSprite1.getGlobalBounds().width,mCurrentGameData->GameWindow.getSize().y -
                                        LandSprite1.getGlobalBounds().height);
    //add them to the vector buffer
    mLandSpritesVector.push_back(LandSprite1);
    mLandSpritesVector.push_back(LandSprite2);
}

void Land::MoveLand(float &DeltaTime, float& HorizontalSpeed){
    //iterate over the vector buffer of lands
    for(unsigned short int idx = 0; idx < mLandSpritesVector.size(); idx++){
        //move it
        float horizontalDisplacement = -HorizontalSpeed * DeltaTime;
        mLandSpritesVector.at(idx).move(horizontalDisplacement,0.f);
        //if off the screen on the left just shift it off the screen to the right for next cycle
        if(mLandSpritesVector.at(idx).getPosition().x<(0-mLandSpritesVector.at(idx).getGlobalBounds().width)){
            //get its full coordinates and shift it
            sf::Vector2f newLandPosition(mCurrentGameData->GameWindow.getSize().x-5,mLandSpritesVector.at(idx).getPosition().y);
            mLandSpritesVector.at(idx).setPosition(newLandPosition);
        }            
    }
}

void Land::DrawLand(){
    //iterate over the vector buffer of lands and draw them
    for(unsigned short int idx = 0; idx < mLandSpritesVector.size(); idx++)
        mCurrentGameData->GameWindow.draw(mLandSpritesVector.at(idx));   
}

const std::vector<sf::Sprite>& Land::GetLandSprites() const{
    return mLandSpritesVector;
}

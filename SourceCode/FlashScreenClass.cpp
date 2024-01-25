#include "FlashScreenClass.h"

FlashScreen::FlashScreen(GameDataShrdPtr CurrentGameData){
    mCurrentGameData = CurrentGameData;
    //initilaze the rectangle shape
    mRectangleShape = sf::RectangleShape(sf::Vector2f(CurrentGameData->GameWindow.getSize()));
    mRectangleShape.setFillColor(sf::Color(255,0,0,0));


    //set the flash boolean
    mIsFlashing = true;
}

void FlashScreen::FlashUpdateOnce(float &deltaTime){
    //flash by changing alpha channel
    if(mIsFlashing == true){
        int AlphaChannel = (int)mRectangleShape.getFillColor().a + (FlasScreenSpeed * deltaTime);
        //in case full transparency reverse
        if(AlphaChannel >= 255.f){
            AlphaChannel = 255.f;
            mIsFlashing = false;
        }
        //set alpha channel
        mRectangleShape.setFillColor(sf::Color(255,0,0,AlphaChannel));
    }
    else{
        int AlphaChannel = (int)mRectangleShape.getFillColor().a - (FlasScreenSpeed * deltaTime);
        //in case full transparency reverse
        if(AlphaChannel <= 0.f){
            AlphaChannel = 0.f;
            mIsFlashing = false;
        }
        //set alpha channel
        mRectangleShape.setFillColor(sf::Color(255,0,0,AlphaChannel));
    }
    

}

void FlashScreen::DrawFlashScreen(){
    mCurrentGameData->GameWindow.draw(mRectangleShape);
}

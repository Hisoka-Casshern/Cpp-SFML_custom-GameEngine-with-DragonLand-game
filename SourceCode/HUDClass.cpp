#include "HUDClass.h"

HUD::HUD(GameDataShrdPtr CurrentGameData){
    this->mCurrentGameData=CurrentGameData;
    //set desired font and initialize it
    mScoreText.setFont(mCurrentGameData->GameAssets.GetFont("Thick Font"));
    //start from zero
    mScoreText.setString("0");
    //set the size
    mScoreText.setCharacterSize(ThickFontSize);
    //set the fill color
    mScoreText.setFillColor(HUDColor);
    //set the orgin position to center it
    mScoreText.setOrigin(mScoreText.getGlobalBounds().width/2.f,
                            mScoreText.getGlobalBounds().height/2.f);
    //as origin is at the center of display box we position it now at half screen
    //an offset down screen
    mScoreText.setPosition(this->mCurrentGameData->GameWindow.getSize().x/2.f + ScreenXOffestHUD,
                           this->mCurrentGameData->GameWindow.getSize().y + ScreenYOffsetHUD);
}

void HUD::UpdateCurrentScoreHUD(int& Score){
    mScoreText.setString(std::to_string(Score));
}

void HUD::DrawHUD(){
    mCurrentGameData->GameWindow.draw(mScoreText);
}

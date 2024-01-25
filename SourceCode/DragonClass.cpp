#include "DragonClass.h"

Dragon::Dragon(GameDataShrdPtr CurrentGameData){
    this->mCurrentGameData = CurrentGameData;

    //fill vector buffer with textures
    mDragonAnimationFramesVector.push_back(CurrentGameData->GameAssets.GetTexture("Dragon Frame 1"));
    mDragonAnimationFramesVector.push_back(CurrentGameData->GameAssets.GetTexture("Dragon Frame 2"));
    mDragonAnimationFramesVector.push_back(CurrentGameData->GameAssets.GetTexture("Dragon Frame 3"));
    mDragonAnimationFramesVector.push_back(CurrentGameData->GameAssets.GetTexture("Dragon Frame 4"));
    mDragonAnimationFramesVector.push_back(CurrentGameData->GameAssets.GetTexture("Dragon Frame 5"));
    mDragonAnimationFramesVector.push_back(CurrentGameData->GameAssets.GetTexture("Dragon Frame 6"));
    mDragonAnimationFramesVector.push_back(CurrentGameData->GameAssets.GetTexture("Dragon Frame 7"));
    mDragonAnimationFramesVector.push_back(CurrentGameData->GameAssets.GetTexture("Dragon Frame 8"));

    //set texture based on vector position
    this->mDragonSprite.setTexture(mDragonAnimationFramesVector.at(mAnimationCounter));

    //set position for dragon
    this->mDragonSprite.setPosition((mCurrentGameData->GameWindow.getSize().x/4.f)-
                                        (mDragonSprite.getGlobalBounds().width/2.f),
                                    (mCurrentGameData->GameWindow.getSize().y/2.f)-
                                        (mDragonSprite.getGlobalBounds().height/2.f));

    //initial state is rigid          
    mDragonState = DragonRigidState;     

    //create a local vector that stores coordinates of the origin of sprite on which local 
    //transformations will be done
    sf::Vector2f DragonSpriteOrigin = sf::Vector2f(mDragonSprite.getGlobalBounds().width/2.f,
                                                    mDragonSprite.getGlobalBounds().height/2.f);
    mDragonSprite.setOrigin(DragonSpriteOrigin);
    mDragonRotation = 0;

}

void Dragon::DrawDragon(){
    this->mCurrentGameData->GameWindow.draw(mDragonSprite);
}

void Dragon::AnimateDragon(){
    //based on set animation framret for dragon animate dragon
    if(this->mSimpleClock.GetElapsedTimeInSeconds() > DragonAnimationFramerate/8.f){
        if(mAnimationCounter < mDragonAnimationFramesVector.size()-1) mAnimationCounter++;
        else mAnimationCounter=0;
        //set texture and reset timer
        mDragonSprite.setTexture(mDragonAnimationFramesVector.at(mAnimationCounter));
        this->mSimpleClock.Restart();
    }

}

void Dragon::DragonUpdate(float &deltaTime){
    //deals with different states of dragon
    if(mDragonState == DragonFlyingState){
        mDragonSprite.move(0,-FlySpeed*deltaTime);

        //rotate it
        mDragonRotation -= DragonRoatationVelocity * deltaTime;
        //force just small rotations
        if(mDragonRotation < -25.f) mDragonRotation = -25.f;
        mDragonSprite.setRotation(mDragonRotation);
    }
    else if(mDragonState == DragonFallingState){
        //move dragon down y axis
        mDragonSprite.move(0,GravityInGame*deltaTime);
        
        //rotate it
        mDragonRotation += DragonRoatationVelocity * deltaTime;
        //force just small rotations
        if(mDragonRotation > 25.f) mDragonRotation = 25.f;
        mDragonSprite.setRotation(mDragonRotation);
    }

    //check the time of max fly capability and if so dragon is falling
    if(mDragonMovementSimpleTimer.GetElapsedTimeInSeconds()>FlyDuration){
        mDragonMovementSimpleTimer.Restart();
        mDragonState = DragonFallingState;
    }
}

void Dragon::UserPressed(){
    //we start by reseting timer as to take account how long between clicks user will press
    mDragonMovementSimpleTimer.Restart();
    //we make dragon fly
    mDragonState = DragonFlyingState;

}

const sf::Sprite& Dragon::GetDragonSprite() const{
   return mDragonSprite;
}

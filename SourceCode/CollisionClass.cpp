#include "CollisionClass.h"

Collision::Collision(){
}

bool Collision::IsCollided(sf::Sprite FirstSprite, sf::Sprite SecondSprite,
                       float FirstSpriteXScale, float FirstSpriteYScale,
                       float SecondSpriteXScale, float SecondSpriteYScale){
    //scale both sprites 
    FirstSprite.scale(FirstSpriteXScale,FirstSpriteYScale);
    SecondSprite.scale(SecondSpriteXScale,SecondSpriteYScale);

    //get the rectangle around each sprite
    sf::Rect<float> FirstSpriteBoundingBox = FirstSprite.getGlobalBounds();
    sf::Rect<float> SecondSpriteBoundingBox = SecondSprite.getGlobalBounds();

    //check collision
    if(FirstSpriteBoundingBox.intersects(SecondSpriteBoundingBox)) return true;
    else return false;
}

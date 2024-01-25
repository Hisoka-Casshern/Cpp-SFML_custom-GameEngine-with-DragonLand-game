#pragma once

#include <SFML/Graphics.hpp>

class Collision{
    public:
        //constructor
        Collision();
        
        //method to check collison between two sprites
        bool IsCollided(sf::Sprite FirstSprite, sf::Sprite SecondSprite,
                       float FirstSpriteXScale, float FirstSpriteYScale,
                       float SecondSpriteXScale, float SecondSpriteYScale);

};
#pragma once

#include <SFML/Graphics.hpp>

//input class
class InputController{
    public:
        //empty constructor and destructor
        InputController(){}
        ~InputController(){}
        
        //getter for mouse position, integer 2d vector
        sf::Vector2i GetMousePosition(sf::RenderWindow& GameWindow);

        //method to check if the sprite in game is clicked
        bool IsSpriteClicked(sf::RenderWindow& GameWindow,
                                sf::Sprite GameCharacterSprite, 
                                    sf::Mouse::Button MouseButton);
};
#include "InputControllerClass.h"

//function implementations
sf::Vector2i InputController::GetMousePosition(sf::RenderWindow &GameWindow){
    //just return the inbuilt sfml function return
    return sf::Mouse::getPosition(GameWindow);
}

bool InputController::IsSpriteClicked(sf::RenderWindow &GameWindow, 
                                        sf::Sprite GameCharacterSprite, 
                                            sf::Mouse::Button MouseButton){
    //check if passed button is pressed, and if so if it is over the sprite
    if(sf::Mouse::isButtonPressed(MouseButton) == true){
        //we create a temporary rectangle bounding box for game character
        sf::IntRect CharacterBoundingBox(GameCharacterSprite.getPosition().x,
                                            GameCharacterSprite.getPosition().y,
                                                GameCharacterSprite.getGlobalBounds().width,
                                                    GameCharacterSprite.getGlobalBounds().height);
        //mouse position
        sf::Vector2i CurrentMousePosition = GetMousePosition(GameWindow);
        //we perform the bool check
        if(CharacterBoundingBox.contains(CurrentMousePosition)) return true;
    }
    //return false if no other conditon met
    return false;
}

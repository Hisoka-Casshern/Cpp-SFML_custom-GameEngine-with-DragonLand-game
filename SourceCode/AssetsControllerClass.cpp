#include "AssetsControllerClass.h"

//implementation of functions
void AssetsController::LoadTexture(std::string TexturePath, std::string TextureName){
    //create a local texture and load fromn file into it
    sf::Texture texture;
    if(texture.loadFromFile(TexturePath)) this->mTextures[TextureName]=texture;
}

sf::Texture& AssetsController::GetTexture(std::string TextureName){
    //return from dictionary a reference to texture
    return this->mTextures.at(TextureName);
}

void AssetsController::LoadFont(std::string FontPath, std::string FontName){
    //create a local font object and load fromn file into it
    sf::Font font;
    if(font.loadFromFile(FontPath)) this->mFonts[FontName]=font;
}

sf::Font& AssetsController::GetFont(std::string FontName){
    //return from dictionary a reference to texture
    return this->mFonts.at(FontName);
}

void AssetsController::LoadSound(std::string SoundPath, std::string SoundName){
    //create local sound buffer and load from path into it, store it in dictionary
    sf::SoundBuffer soundBuffer;
    if(soundBuffer.loadFromFile(SoundPath)) this->mSounds[SoundName] = soundBuffer;

}

sf::SoundBuffer& AssetsController::GetSound(std::string SoundName){
    //return from dictionary a refrence to specific sound
    return this->mSounds.at(SoundName);
}


#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <unordered_map>

//the class that manages loading and maniuplating of game assets
class AssetsController{
    public:
        //empty constructor and destructor
        AssetsController(){}
        ~AssetsController(){}

        //texture loader function, takes the name for a texture and a filepath
        void LoadTexture(std::string TexturePath, std::string TextureName);
        //getter for sfml texture
        sf::Texture& GetTexture(std::string TextureName);

        //font loader
        void LoadFont(std::string FontPath, std::string FontName);
        //getter for sfml font
        sf::Font& GetFont(std::string FontName);

        //sound loader
        void LoadSound(std::string SoundPath, std::string SoundName);
        //sound getter
        sf::SoundBuffer& GetSound(std::string SoundName);

    private:
        //we store dictionaries
        std::unordered_map<std::string, sf::Texture> mTextures;
        std::unordered_map<std::string, sf::Font> mFonts;
        std::unordered_map<std::string, sf::SoundBuffer> mSounds;
};
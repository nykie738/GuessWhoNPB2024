#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(const std::string& name, const std::string& team, const std::string& imagePath);
    
    std::string getName() const { return name; }
    std::string getTeam() const { return team; }
    std::string getImagePath() const { return imagePath; }
    const sf::Texture& getTexture() const { return texture; }

private:
    std::string name;
    std::string team;
    std::string imagePath;
    sf::Texture texture;
};
#include "Player.h"

Player::Player(const std::string& name, const std::string& team, const std::string& imagePath)
    : name(name), team(team), imagePath(imagePath) {
    if (!texture.loadFromFile(imagePath)) {
        // Handle error - maybe load a default "image not found" texture
    }
}
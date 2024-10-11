#include "PlayerManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

PlayerManager::PlayerManager() : rng(std::random_device{}()) {}

void PlayerManager::loadPlayers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open player data file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, team, imagePath;

        if (std::getline(iss, name, ',') &&
            std::getline(iss, team, ',') &&
            std::getline(iss, imagePath)) {
            players.emplace_back(name, team, imagePath);
        }
    }
}

const Player& PlayerManager::getRandomPlayer() {
    if (players.empty()) {
        throw std::runtime_error("No players loaded");
    }
    std::uniform_int_distribution<> dist(0, players.size() - 1);
    return players[dist(rng)];
}
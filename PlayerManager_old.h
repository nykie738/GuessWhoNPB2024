#pragma once
#include "Player.h"
#include <vector>
#include <random>

class PlayerManager {
public:
    PlayerManager();
    void loadPlayers(const std::string& filename);
    const Player& getRandomPlayer();
    size_t getPlayerCount() const { return players.size(); }

private:
    std::vector<Player> players;
    std::mt19937 rng;
};
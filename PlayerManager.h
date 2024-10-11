#pragma once
#include "Player.h"
#include <vector>
#include <random>
#include <unordered_map>

class PlayerManager {
public:
    PlayerManager();
    void loadPlayers(const std::string& filename);
    const Player& getRandomPlayer();
    const Player& getRandomPlayerByTeam(const std::string& team);
    size_t getPlayerCount() const { return players.size(); }
    std::vector<std::string> getTeams() const;

private:
    std::vector<Player> players;
    std::unordered_map<std::string, std::vector<size_t>> teamPlayerIndices;
    std::mt19937 rng;
};
#include "PlayerManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

PlayerManager::PlayerManager() : rng(std::random_device{}()) {}

void PlayerManager::loadPlayers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open player data file: " + filename);
    }

    players.clear();
    teamPlayerIndices.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, team, imagePath;

        if (std::getline(iss, name, ',') &&
            std::getline(iss, team, ',') &&
            std::getline(iss, imagePath)) {
            players.emplace_back(name, team, imagePath);
            teamPlayerIndices[team].push_back(players.size() - 1);
        }
    }

    if (players.empty()) {
        throw std::runtime_error("No players loaded from file: " + filename);
    }
}

const Player& PlayerManager::getRandomPlayer() {
    if (players.empty()) {
        throw std::runtime_error("No players loaded");
    }
    std::uniform_int_distribution<> dist(0, players.size() - 1);
    return players[dist(rng)];
}

const Player& PlayerManager::getRandomPlayerByTeam(const std::string& team) {
    auto it = teamPlayerIndices.find(team);
    if (it == teamPlayerIndices.end() || it->second.empty()) {
        throw std::runtime_error("No players found for team: " + team);
    }
    std::uniform_int_distribution<> dist(0, it->second.size() - 1);
    return players[it->second[dist(rng)]];
}

std::vector<std::string> PlayerManager::getTeams() const {
    std::vector<std::string> teams;
    teams.reserve(teamPlayerIndices.size());
    for (const auto& pair : teamPlayerIndices) {
        teams.push_back(pair.first);
    }
    return teams;
}
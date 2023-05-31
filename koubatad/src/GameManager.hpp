#pragma once

#include "Menu.hpp"
#include "Object.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include "Crate.hpp"
#include "Enemy.hpp"
#include "BuffBomb.hpp"
#include "BuffDetonator.hpp"
#include "BuffHeal.hpp"
#include "BuffLevitate.hpp"
#include "BuffRadius.hpp"

#include <vector>
#include <memory>
#include <utility>
#include <random>
#include <chrono>
#include <thread>

/**
 * @brief Main game object - Manages all game objects and runs the game
 *
 */
class GameManager : public Menu
{
public:
    explicit GameManager(bool multi, std::string &map, std::string &score, std::string &conf, bool test = false);

    void runMenu() override;

private:
    bool m_Multi = false;
    bool m_Player1Winner = true;
    bool m_Test;
    int m_Score = 0;
    const int GAME_WINDOW_HEIGHT = 15;
    const int GAME_WINDOW_WIDTH = 15;
    /**
     * @brief Stores configuration values
     */
    struct Config
    {
        int m_MonsterScore = 100; // Score for monster kill
        int m_BonusScore = 50; // Score for picking up bonus
        double m_DropChance = 0.5; // Chance of a bonus to drop from Crate
        double m_LevitateChance = 0.2; // Chance of Levitate drop
        double m_DetonatorChance = 0.2; // Chance of Detonator drop
        double m_BombChance = 0.2; // Chance of additional Bomb drop
        double m_RadiusChance = 0.2; // Chance of Radius increase drop
        double m_HealChance = 0.2; // Chance of Heal drop
    };
    Config m_Config;

    std::string m_MapPath;
    std::string m_ScorePath;
    std::string m_ConfigPath;
    std::chrono::steady_clock::time_point m_StartTime;

    std::vector<std::shared_ptr<Object>> m_Objects; // All the object present in game
    std::vector<std::shared_ptr<Entity>> m_Entities; // All entity objects
    std::shared_ptr<Player> m_Player1 = nullptr; // Player1 object
    std::shared_ptr<Player> m_Player2 = nullptr; // Player2 object
    std::vector<std::shared_ptr<Bomb>> m_Bombs; // Bomb objects
    std::vector<std::shared_ptr<Special>> m_Special; // Special objects

    /**
     * @brief Generate map based on chosen map file
     */
    void generateMap();

    /**
     * @brief Prints current stats to the screen
     */
    void printStats();

    /**
     * @brief Read configuration from file in path
     * @param path Path to map file file
     * @throws String error if file couldn't be opened or closed or if configuration in it is corrupted
     *
     */
    std::string readMapFile(const std::string &path);

    /**
     * @brief Parse file, save constants
     * @param file File to be parsed
     *
     */
    std::string parseMapFile(std::ifstream &file);

    void createWall(std::pair<int, int> coord);

    void createCrate(std::pair<int, int> coord);

    void createEnemy(std::pair<int, int> coord);

    void createPlayer1(std::pair<int, int> coord);

    void createPlayer2(std::pair<int, int> coord);

    void createBonus(std::pair<int, int> coord, int bonus = 0);

    double getElapsedTime() const;

    int readInput(int &currSelect) override;

    void takeAction(int action) override;

    void displayCustom() override
    {};

    /**
     * @brief Explode bomb, remove it from objects, create explosion
     * @param bomb Bomb to be exploded
     */
    void explodeBomb(std::shared_ptr<Bomb> &bomb);

    void handleCollision(const std::shared_ptr<Special> &special);

    /**
     * @brief Check if given object is in Entity vector, if so removes it
     * @param obj Object to check presence of
     * @return True if object found, False otherwise
     */
    bool checkEntity(const std::shared_ptr<Object> &obj);

    /**
     * @brief Check if given object is in Special vector, if so removes it
     * @param obj Object to check presence of
     * @return True if object found, False otherwise
     */
    bool checkSpecial(const std::shared_ptr<Object> &obj);

    /**
     * @brief Displays winner window
     */
    void displayWinner();

    /**
     * @brief Check if new high score has been achieved, if so prompt player to input name
     */
    void saveScore();

    /**
     * @brief Save new high scores to file
     * @param scores map of mapID:Name:Score
     */
    void writeScore(const std::map<int, std::pair<std::string, int>> &scores);

    /**
     * @brief Read configuration file
     */
    void readConfig();

    /**
     * @brief Load configuration, if invalid use default
     */
    void parseConfig( std::vector<std::pair<std::string, double>>& values);
};




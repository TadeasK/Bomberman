#pragma once

#include "Menu.hpp"
#include "Object.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include "Crate.hpp"
#include "Enemy.hpp"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

class GameManager : public Menu {
public:
    explicit GameManager(bool multi, std::string &map);

    void runMenu() override;

private:
    bool m_Multi = false;
    int m_Score = 0;
    const int GAME_WINDOW_HEIGHT = 15;
    const int GAME_WINDOW_WIDTH = 15;
    std::string m_MapPath;

    std::vector<std::shared_ptr<Object>> m_Objects; // All the object present in game
    std::vector<std::shared_ptr<Entity>> m_Entities; // All entity objects
    std::shared_ptr<Player> m_Player1; // Player1 object
    std::shared_ptr<Player> m_Player2; // Player2 object

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
    std::string readConfig(const std::string &path);

    /**
     * @brief Parse file, save constants
     * @param file File to be parsed
     *
     */
    std::string parseFile(std::ifstream &file);

    void createWall(int x, int y);

    void createCrate(int x, int y, bool isFull);

    void createEnemy(int x, int y);

    void createPlayer1(int x, int y);

    void createPlayer2(int x, int y);

    int readInput(size_t &currSelect) override;

    void takeAction(size_t action) override;
};




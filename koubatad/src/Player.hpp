#pragma once

#include "Entity.hpp"
#include "Bomb.hpp"
#include <vector>
#include <memory>

/**
 * @brief A class representing a Player entity 
 * 
 */
class Player : public Entity {
public:
    /**
     * @brief Construct a new Player object
     * 
     * @param x An X position of new Player
     * @param y An Y position of new Player
     * @param window Window, where Player is displayed
     * @param color Color of player
     * @param speed Movement speed of Player
     * @param bombRadius Explosion radius of player's bombs
     * @param bombsCount Maximum number of bombs player is allowed to place at the same time
     * @param bombThrow Range at which player can throw bomb
     * @param bombTimer Time until player placed bombs explode
     * @param health Health of player
     */
    Player(int x, int y, WINDOW *window, int color = 4, int speed = 1, int bombRadius = 1, int bombsCount = 1,
           int bombTimer = 5, int health = 3);

    int getHealth() const;

    bool drawObj() const override;

    virtual void receiveEffect ( int effect ) override;

    void move() override;

    /**
     * @brief Sets Player direction, which will be evaluated when move() is called
     * @param dir New direction of player
     */
    void setMove(size_t dir);

    /**
     * @brief Places bomb at player's feet/throw a bomb
     *
     * @param x An X position where to place the bomb
     * @param y An Y position where to place the bomb
     * @param radius Radius of bomb explosion
     * @return true If place successful
     * @return false If bomb can not be placed
     */
    std::shared_ptr<Bomb> placeBomb();


private:
    enum DIR_OPTIONS {
        MOVE_UP = 1, MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN
    };
    int m_Color; // Color of player on the map
    int m_Dir = 0; // Direction of player
    const char m_Repr = '@'; // Constant character representing the player on the map
    int m_BombRadius; // Current radius of player placed bombs
    size_t m_BombsCount; // Current maximum count of bombs player can place at the same time
    std::vector<std::shared_ptr<Bomb>> m_BombsPlaced;
    int m_BombTimer; // How long it takes for bombs placed by this player to explode
    int m_Health;
    bool m_Levitate = false;
    bool m_Detonator = false;

    /**
     * @brief Sets player's direction to UP, checking if he can move that way
     * @return True if movement possible, False otherwise
     */
    bool moveUp();

    /**
     * @brief Sets player's direction to LEFT, checking if he can move that way
     * @return True if movement possible, False otherwise
     */
    bool moveLeft();

    /**
     * @brief Sets player's direction to RIGHT, checking if he can move that way
     * @return True if movement possible, False otherwise
     */
    bool moveRight();

    /**
     * @brief Sets player's direction to DOWN, checking if he can move that way
     * @return True if movement possible, False otherwise
     */
    bool moveDown();

    /**
     * @brief Check if movement to given coordinates is possible
     * @return True if movement possible, False otherwise
     */
    bool checkConstrains(int x, int y) override;

    /**
     * @brief Checks status of bombs, removes exploded bombs
     */
    void checkBombs();

    /**
     * @brief Check health status, set Exist status to false if health <= 0
     */
    void checkHealth();
};
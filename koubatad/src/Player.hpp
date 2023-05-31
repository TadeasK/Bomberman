#pragma once

#include "Entity.hpp"
#include "Bomb.hpp"
#include <vector>
#include <chrono>
#include <memory>
#include <cctype>

/**
 * @brief A class representing a Player entity 
 * 
 */
class Player : public Entity
{
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
     * @param bombTimer Time until player placed bombs explode
     * @param health Health of player
     */
    Player(int x, int y, WINDOW *window, int color = 4, int speed = 1, int bombRadius = 1, int bombsCount = 1,
           int bombTimer = 5, int health = 3);

    /**
     * @return Current player health count
     */
    int getHealth() const;

    virtual bool drawObj() const override;

    virtual void receiveEffect(int effect) override;

    virtual void move(const std::pair<int, int> &playerPos) override;

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
    /// Options of movement for player
    enum DIR_OPTIONS
    {
        MOVE_UP = 1, MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN
    };
    /// Color of player on the map
    int m_Color;
    /// Direction of player
    int m_Dir = 0;
    /// Character representing the player on the map
    const char m_Repr = '@';
    /// Current radius of player placed bombs
    int m_BombRadius;
    /// Current maximum count of bombs player can place at the same time
    size_t m_BombsCount;
    /// Vector of currently placed bombs
    std::vector<std::shared_ptr<Bomb>> m_BombsPlaced;
    /// Array of timepoints where [0] invulnerability, [1], Levitation, [2] Detonator
    std::chrono::steady_clock::time_point m_TimePoints[3];

    /// How long it takes for bombs placed by this player to explode
    int m_BombTimer;
    /// Health of player
    int m_Health;
    /// If player has levitation buff (can pass enemies, explosions)
    bool m_Levitate = false;
    /// If player can detonate bombs remotely
    bool m_Detonator = false;
    /// Player is invulnerable for a short time after receiving damage
    bool m_Invulnerable = false;

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

    /**
     * @brief Checks active effects and turns them off if timer has run out
     */
    void checkState();

    /**
     * @brief Damages player, sets him into invulnerable state for a duration
     */
    void takeDamage();

    /**
     * @brief Start timer for given effect
     * @param timerType Type of effect
     */
    void startTimer(int timerType);
};
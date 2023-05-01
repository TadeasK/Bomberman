#pragma once

#include "Entity.hpp"
#include "Bomb.hpp"
#include <vector>

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
           int bombThrow = 0, int bombTimer = 5, int health = 3);

    int getHealth() const;

    void drawObj() const override;

    void move() override;

    /**
     * @brief Sets Player into state, which will be evaluated when move() is called
     * @param action Value of action
     */
    void setAction(size_t action);

private:
    enum STATE_OPTIONS {
        MOVE_UP = 1, MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN, PLACE_BOMB
    };
    int m_Color; // Color of player on the map
    int m_State = 0; // State of player
    const char m_Repr = '@'; // Constant character representing the player on the map
    int m_BombRadius; // Current radius of player placed bombs
    size_t m_BombsCount; // Current maximum count of bombs player can place at the same time
    int m_BombThrow; // Max range at which player can place a bomb
    int m_BombTimer; // How long it takes for bombs placed by this player to explode
    int m_Health;
    std::vector<Bomb> m_BombsPlaced; // Current number of bombs placed


    /**
     * @brief Places bomb at player's feet/throw a bomb
     *
     * @param x An X position where to place the bomb
     * @param y An Y position where to place the bomb
     * @param radius Radius of bomb explosion
     * @return true If place successful
     * @return false If bomb can not be placed
     */
    bool placeBomb();

    bool moveUp();

    bool moveLeft();

    bool moveRight();

    bool moveDown();

    bool checkConstrains(int x, int y) override;
};
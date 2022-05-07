#pragma once

#include "Entity.hpp"

/**
 * @brief A class representing a Player entity 
 * 
 */
class Player: public Entity
{
public:
    /**
     * @brief Construct a new Player object
     * 
     * @param x An X position of new Player
     * @param y An Y position of new Player
     * @param speed Movement speed of Player
     * @param bombRadius Explosion radius of player's bombs
     * @param bombsCount Maximum number of bobms player is allowed to place at the same time
     * @param bombThrow Range of player's bomb throw
     */
    Player( int x, int y, int speed, int bombRadius = 0, int bombsCount = 1);
    ~Player() {};

    virtual bool drawObj() const override;

    virtual void move() override;

    /**
     * @brief Places bomb at player's feet/throw a bomb
     * 
     * @param x An X position where to place the bomb 
     * @param y An Y position where to place the bomb
     * @param radius Radius of bomb explosion
     * @return true If place succesfull
     * @return false If bomb can not be placed
     */
    bool placeBomb ();

private:
    int m_BombRadius; // Current radius of player placed bombs
    int m_BombsCount; // Current maximum count of bombs player can place at the same time
    int m_BombThrow = 0; // Max range at which player can place a bomb
    int m_BombsPlaced = 0; // Current number of bombs placed
};
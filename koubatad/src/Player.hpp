#pragma once

#include "Entity.hpp"
#include "Bomb.hpp"
#include <vector>

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
     * @param bombsCount Maximum number of bombs player is allowed to place at the same time
     */
    Player( int x, int y, int speed, int bombRadius, int bombsCount, int bombThrow, int bombTimer);
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
    const char m_Repr = '@'; // Constant character representing the player on the map
    int m_BombRadius; // Current radius of player placed bombs
    int m_BombsCount; // Current maximum count of bombs player can place at the same time
    int m_BombThrow; // Max range at which player can place a bomb
    int m_BombTimer; // How long it takes for bombs placed by this player to explode
    std::vector<Bomb> m_BombsPlaced; // Current number of bombs placed
};
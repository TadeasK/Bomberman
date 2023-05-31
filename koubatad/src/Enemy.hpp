#pragma once

#include "Entity.hpp"
#include <random>

/**
 * @brief A class representing Enemy (AI controlled) entity 
 * 
 */
class Enemy : public Entity
{
public:
    /**
     * @brief Construct a new Enemy object
     * 
     * @param x An X position of new Enemy
     * @param y An Y position of new Enemy
     * @param speed Movement speed of Enemy 
     * @param window Window, where object is displayed
     */
    Enemy(int x, int y, WINDOW *window, int speed);

    virtual bool drawObj() const override;

    virtual void move(const std::pair<int, int> &playerPos) override;

    virtual void receiveEffect(int effect) override;

private:
    /// Delays enemy movement
    int m_Delay = rand() % 3001;
    /// Times enemy has not moved
    int m_NotMoved = 0;
    /// Count of default moves remaining
    int m_DefaultMoves = 0;
    /// Different states enemy can be in
    enum STATE_OPTIONS
    {
        MOVE_UP = 1, MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT
    };
    /// State of Enemy { most significant move, second second most significant move }
    std::pair<int, int> m_State ={1,2};
    /// Char representing Enemy on game window
    const char m_Repr = '$';

    bool checkConstrains(int x, int y) override;

    /**
     * @brief Set state based on player position
     * @param playerPos Position of player
     */
    void setState(const std::pair<int, int> &playerPos);

    /**
     * @brief Switch movement state of Enemy
     */
    void switchStates();

    /**
     * @brief Perform default move
     */
    void defaultMove();
};
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

    bool drawObj() const override;

    void move(const std::pair<int, int> &playerPos) override;

    virtual void receiveEffect(int effect) override;

private:
    int m_Delay = rand() % 3001; // Delays enemy movement
    int m_NotMoved = 0;
    int m_DefaultMoves = 0;
    enum STATE_OPTIONS
    {
        MOVE_UP = 1, MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT
    };
    // State of Enemy { most significant move, second second most significant move }
    std::pair<int, int> m_State ={1,2};
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

    void defaultMove();
};
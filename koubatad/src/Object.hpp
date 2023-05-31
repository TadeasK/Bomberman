#pragma once

#include "ncurses.h"
#include <utility>

/**
 * @brief A class representing any object in the game 
 * 
 */
class Object
{
public:
    /**
     * @brief Construct a new Object at given position
     * 
     * @param x An X position of object 
     * @param y A Y position of object
     * @param window Window where object is to be displayed
     */
    Object(int x, int y, WINDOW *window);

    virtual ~Object() = default;

    /**
     * @brief Draws object into environment 
     * 
     * @return true If drawn successfully
     * @return false If object doesn't exist anymore
     */
    virtual bool drawObj() const = 0;

    /**
     * @brief Makes Object receive given effect
     * @param effect Effect to receive
     */
    virtual void receiveEffect(int effect);

    /**
     * @brief Get current Object position
     * @return Current position
     */
    virtual std::pair<int, int> getPosition() const;

    /// Various effects
    enum EFFECT
    {
        DAMAGE, LEVITATE, DETONATOR, BOMB_INC, RADIUS_INC, HEAL, EXPLOSION,
    };

protected:
    /// Window where object is displayed
    WINDOW *m_Window;
    /// A current X position of object
    int m_X;
    /// A current  Y position of object
    int m_Y;
    /// If object exists or if it has been destroyed/killed
    bool m_Exist = true;

    const int GAME_WINDOW_HEIGHT = 15;
    const int GAME_WINDOW_WIDTH = 15;
};
#pragma once

#include "Object.hpp"

/**
 * @brief A class representing Crate object
 *
 */
class Crate : public Object
{
public:

    /**
     * @brief Construct a new Crate object
     *
     * @param x An X position of new Crate
     * @param y An Y position of new Crate
     * @param window Window, where object is displayed
     */
    Crate(int x, int y, WINDOW *window);

    virtual bool drawObj() const override;

    virtual void receiveEffect(int effect) override;

private:
    /// Char representing Crate on game window
    const char m_Repr = '#';

};
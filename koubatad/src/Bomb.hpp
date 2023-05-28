#pragma once

#include "Object.hpp"
#include "Explosion.hpp"
#include <chrono>
#include <vector>
#include <cmath>
#include <memory>

/**
 * @brief A class representing Bomb object
 * 
 */
class Bomb: public Object
{
public:
    /**
     * @brief Construct a new Bomb object
     * 
     * @param x An X position of new Bomb
     * @param y An Y position of new Bomb
     * @param window Window, where object is displayed
     * @param timer Time in seconds until explosion
     * @param radius Radius of explosion
     */
    Bomb( int x, int y, WINDOW* window, int timer = 5, int radius = 1);
   
    bool drawObj() const override;

    void action();

    /**
     * @brief Draws explosion in radius, destroys destroyable objects
     *
     */
    std::vector<std::shared_ptr<Explosion>> explode();

    bool m_Exploded = false; // Activity of bomb
private:
    int m_FusionTimer; // Fusion time (until explosion)
    int m_Timer; // Current time until explosion
    int m_Radius; // Radius of explosion
    std::chrono::steady_clock::time_point m_PlacedTime;

    /**
     * @brief Counts down timer, at 0 explodes
     *
     */
    void countDown();

    double getElapsedTime() const;

};
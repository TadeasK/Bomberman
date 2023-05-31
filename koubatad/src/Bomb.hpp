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
class Bomb : public Object
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
    Bomb(int x, int y, WINDOW *window, int timer, int radius);

    bool drawObj() const override;

    /**
     * @brief Operates bomb timer, status
     */
    void action();

    /**
     * @brief Draws explosion in radius, destroys destroyable objects
     *
     */
    std::vector<std::shared_ptr<Explosion>> explode();
    /// Activity of bomb
    bool m_Exploded = false;
private:
    /// Fusion time (until explosion)
    int m_FusionTimer;
    /// Current time until explosion
    int m_Timer;
    /// Radius of explosion
    int m_Radius;
    /// Time of bomb placement
    std::chrono::steady_clock::time_point m_PlacedTime;

    /**
     * @brief Counts down timer, at 0 explodes
     *
     */
    void countDown();

    /**
     * @brief Calculate elapsed time since bomb was places
     * @return Time since placement
     */
    double getElapsedTime() const;

};
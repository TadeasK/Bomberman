#include "Bomb.hpp"

Bomb::Bomb( int x, int y, WINDOW* window, int timer, int radius )
: Object( x, y, window )
{
    m_FusionTimer = timer;
    m_Timer = timer;
    m_Radius = radius;
    m_PlacedTime = std::chrono::steady_clock::now();
}

void Bomb::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(8));
    mvwprintw(m_Window,m_Y, m_X, "%d", m_Timer);
    wattroff(m_Window, COLOR_PAIR(8));
}
//----------------------------------------------------------------------------------------------
void Bomb::action() {
    countDown();
    if (m_Timer <= 0) {
        explode();
        return;
    }
}
//----------------------------------------------------------------------------------------------
void Bomb::countDown()
{
    auto elapsed = getElapsedTime();
    m_Timer = static_cast<int>(std::round(m_FusionTimer)) - elapsed;
    }
//----------------------------------------------------------------------------------------------

void Bomb::explode()
{
    m_Exploded = true;
    //m_Explosion.push_back('+');
}
//----------------------------------------------------------------------------------------------
double Bomb::getElapsedTime() const {
    auto currTimePoint = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currTimePoint - m_PlacedTime;
    return elapsedTime.count();
}
//----------------------------------------------------------------------------------------------
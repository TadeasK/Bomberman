#include "Bomb.hpp"

Bomb::Bomb(int x, int y, WINDOW *window, int timer, int radius)
        : Object(x, y, window)
{
    m_FusionTimer = timer;
    m_Timer = timer;
    m_Radius = radius;
    m_PlacedTime = std::chrono::steady_clock::now();
}

//----------------------------------------------------------------------------------------------
bool Bomb::drawObj() const
{
    if ( m_Exist ) {
        wattron(m_Window, COLOR_PAIR(8));
        mvwprintw(m_Window, m_Y, m_X, "%d", m_Timer);
        wattroff(m_Window, COLOR_PAIR(8));
    }
    else
        mvwprintw(m_Window, m_Y, m_X, " ");
    return m_Exist;
}

//----------------------------------------------------------------------------------------------
void Bomb::action()
{
    countDown();
    if (m_Timer <= 0) {
        m_Exploded = true;
        m_Exist = false;
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

std::vector<std::shared_ptr<Explosion>> Bomb::explode()
{
    std::vector<std::shared_ptr<Explosion>> tmp;
    tmp.emplace_back(std::make_shared<Explosion>(m_X, m_Y, m_Window));
    for (int i = 1; i <= m_Radius; ++i) {
        tmp.emplace_back(std::make_shared<Explosion>(m_X + i, m_Y, m_Window));
        tmp.emplace_back(std::make_shared<Explosion>(m_X - i, m_Y, m_Window));
        tmp.emplace_back(std::make_shared<Explosion>(m_X, m_Y + i, m_Window));
        tmp.emplace_back(std::make_shared<Explosion>(m_X, m_Y - i, m_Window));
    }
    return tmp;
}

//----------------------------------------------------------------------------------------------
double Bomb::getElapsedTime() const
{
    auto currTimePoint = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currTimePoint - m_PlacedTime;
    return elapsedTime.count();
}
//----------------------------------------------------------------------------------------------
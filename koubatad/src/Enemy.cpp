#include "Enemy.hpp"

Enemy::Enemy(int x, int y, WINDOW *window, int speed)
        : Entity(x, y, window, speed)
{}
//----------------------------------------------------------------------------------------------

bool Enemy::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(7));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(7));
    return m_Exist;
}
//----------------------------------------------------------------------------------------------

void Enemy::move(const std::pair<int, int> &playerPos)
{
    if (m_Delay < 4000) {
        m_Delay++;
        return;
    }
    m_Delay = 0;
    if (m_NotMoved > 4 && m_DefaultMoves == 0) {
        m_DefaultMoves = 10;
    }

    if (m_DefaultMoves > 0) {
        defaultMove();
        return;
    }

    setState(playerPos);
    int moved = 4;
    while (--moved > 0) {
        switch (m_State.first) {
            case MOVE_UP:
                if (checkConstrains(m_X, m_Y - m_Speed)) {
                    mvwprintw(m_Window, m_Y, m_X, " ");
                    m_Y -= m_Speed;
                    moved = 0;
                    m_NotMoved--;
                }
                else
                    switchStates();
                break;
            case MOVE_LEFT:
                if (checkConstrains(m_X - m_Speed, m_Y)) {
                    mvwprintw(m_Window, m_Y, m_X, " ");
                    m_X -= m_Speed;
                    moved = 0;
                    m_NotMoved--;
                }
                else
                    switchStates();
                break;
            case MOVE_DOWN:
                if (checkConstrains(m_X, m_Y + m_Speed)) {
                    mvwprintw(m_Window, m_Y, m_X, " ");
                    m_Y += m_Speed;
                    moved = 0;
                    m_NotMoved--;
                }
                else
                    switchStates();
                break;
            case MOVE_RIGHT:
                if (checkConstrains(m_X + m_Speed, m_Y)) {
                    mvwprintw(m_Window, m_Y, m_X, " ");
                    m_X += m_Speed;
                    moved = 0;
                    m_NotMoved--;
                }
                else
                    switchStates();
                break;
        }
    }
    m_NotMoved++;
}

//----------------------------------------------------------------------------------------------
void Enemy::defaultMove()
{
    switch (m_State.first) {
        case MOVE_UP:
            if (checkConstrains(m_X, m_Y - m_Speed)) {
                mvwprintw(m_Window, m_Y, m_X, " ");
                m_Y -= m_Speed;
                break;
            }
            else
                m_State.first++;
        case MOVE_LEFT:
            if (checkConstrains(m_X - m_Speed, m_Y)) {
                mvwprintw(m_Window, m_Y, m_X, " ");
                m_X -= m_Speed;
                break;
            }
            else
                m_State.first++;
        case MOVE_DOWN:
            if (checkConstrains(m_X, m_Y + m_Speed)) {
                mvwprintw(m_Window, m_Y, m_X, " ");
                m_Y += m_Speed;
                break;
            }
            else
                m_State.first++;
        case MOVE_RIGHT:
            if (checkConstrains(m_X + m_Speed, m_Y)) {
                mvwprintw(m_Window, m_Y, m_X, " ");
                m_X += m_Speed;
                break;
            }
            else
                m_State.first = 1;
    }
    if (--m_DefaultMoves == 0)
        m_NotMoved = 0;
}
//----------------------------------------------------------------------------------------------

bool Enemy::checkConstrains(int x, int y)
{
    if (x <= 0 || y <= 0 || x >= GAME_WINDOW_WIDTH - 1 || y >= GAME_WINDOW_HEIGHT - 1)
        return false;
    chtype screenObj = mvwinch(m_Window, y, x);
    chtype screenChar = screenObj & A_CHARTEXT;
    if (screenChar == ' ')
        return true;
    if (screenChar == 'H' || screenChar == 'D' || screenChar == 'B'
        || screenChar == 'L' || screenChar == 'R' || screenChar == '@')
        return true;
    return false;
}
//----------------------------------------------------------------------------------------------

void Enemy::receiveEffect(int effect)
{
    if (effect == EXPLOSION)
        m_Exist = false;
}
//----------------------------------------------------------------------------------------------

void Enemy::setState(const std::pair<int, int> &playerPos)
{
    int xDiff = playerPos.first - m_X;
    int yDiff = playerPos.second - m_Y;
    int absX = abs(xDiff);
    int absY = abs(yDiff);
    if (absX >= absY) {
        if (xDiff > 0) {
            m_State.first = MOVE_RIGHT;
            m_State.second = yDiff > 0 ? MOVE_UP : MOVE_DOWN;
        }
        else if (xDiff < 0) {
            m_State.first = MOVE_LEFT;
            m_State.second = yDiff > 0 ? MOVE_UP : MOVE_DOWN;
        }
    }
    else {
        if (yDiff > 0) {
            m_State.first = MOVE_DOWN;
            m_State.second = xDiff > 0 ? MOVE_RIGHT : MOVE_LEFT;
        }
        else if (yDiff < 0) {
            m_State.first = MOVE_UP;
            m_State.second = xDiff > 0 ? MOVE_RIGHT : MOVE_LEFT;
        }
    }
}
//----------------------------------------------------------------------------------------------

void Enemy::switchStates()
{
    m_State.first = m_State.second;
    m_State.second = (m_State.second + 1) % 4 + 1;
}
//----------------------------------------------------------------------------------------------

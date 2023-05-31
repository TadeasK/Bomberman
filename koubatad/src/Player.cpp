#include "Player.hpp"


Player::Player(int x, int y, WINDOW *window, int color, int speed, int bombRadius, int bombsCount,
               int bombTimer, int health) : Entity(x, y, window, speed)
{
    m_Color = color;
    m_BombRadius = bombRadius;
    m_BombsCount = bombsCount;
    m_BombTimer = bombTimer;
    m_Health = health;
}

//----------------------------------------------------------------------------------------------
bool Player::drawObj() const
{
    wattron(m_Window, COLOR_PAIR(m_Color));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(m_Color));
    return m_Exist;
}

//----------------------------------------------------------------------------------------------
void Player::move(const std::pair<int, int>& playerPos)
{
    checkBombs();
    checkHealth();
    checkState();
    switch (m_Dir) {
        case MOVE_UP:
            moveUp();
            break;
        case MOVE_LEFT:
            moveLeft();
            break;
        case MOVE_DOWN:
            moveDown();
            break;
        case MOVE_RIGHT:
            moveRight();
            break;
        default:
            break;
    }

    m_Dir = 0;
}

//----------------------------------------------------------------------------------------------
void Player::setMove(size_t dir)
{
    switch (dir) {
        case 'w':
        case KEY_UP:
            m_Dir = MOVE_UP;
            break;
        case 'a':
        case KEY_LEFT:
            m_Dir = MOVE_LEFT;
            break;
        case 's':
        case KEY_DOWN:
            m_Dir = MOVE_DOWN;
            break;
        case 'd':
        case KEY_RIGHT:
            m_Dir = MOVE_RIGHT;
            break;
        default:
            break;
    }
}

//----------------------------------------------------------------------------------------------
std::shared_ptr<Bomb> Player::placeBomb()
{
    if ( m_Detonator && !m_BombsPlaced.empty() ) {
        for ( auto &x: m_BombsPlaced )
            x->explode();
        return nullptr;
    }

    if (m_BombsPlaced.size() >= m_BombsCount)
        return nullptr;

    auto bomb = std::make_shared<Bomb>(m_X, m_Y, m_Window, m_BombTimer, m_BombRadius);
    m_BombsPlaced.push_back(bomb);
    return bomb;
}

//----------------------------------------------------------------------------------------------
void Player::checkBombs()
{
    for (auto bombIt = m_BombsPlaced.begin(); bombIt != m_BombsPlaced.end();) {
        if ((*bombIt)->m_Exploded)
            bombIt = m_BombsPlaced.erase(bombIt);
        else
            ++bombIt;
    }
}

//----------------------------------------------------------------------------------------------
bool Player::moveUp()
{
    if (!checkConstrains(m_X, m_Y - m_Speed))
        return false;
    m_Y -= m_Speed;
    return true;
}

//----------------------------------------------------------------------------------------------
bool Player::moveLeft()
{
    if (!checkConstrains(m_X - m_Speed, m_Y))
        return false;
    m_X -= m_Speed;
    return true;
}

//----------------------------------------------------------------------------------------------
bool Player::moveRight()
{
    if (!checkConstrains(m_X + m_Speed, m_Y))
        return false;
    m_X += m_Speed;
    return true;
}
//----------------------------------------------------------------------------------------------

bool Player::moveDown()
{
    if (!checkConstrains(m_X, m_Y + m_Speed))
        return false;
    m_Y += m_Speed;
    return true;
}

//----------------------------------------------------------------------------------------------
int Player::getHealth() const
{
    return m_Health;
}

//----------------------------------------------------------------------------------------------
bool Player::checkConstrains(int x, int y)
{
    if (x <= 0 || y <= 0 || x >= GAME_WINDOW_WIDTH-1 || y >= GAME_WINDOW_HEIGHT-1) // Out of window bounds
        return false;

    chtype screenObj = mvwinch(m_Window, y, x);
    chtype screenChar = screenObj & A_CHARTEXT;
    if (screenChar == ' ') // Movement clear
        return true;
    if (screenChar == '#' || screenChar == 'X') // Collision with wall or crate
        return false;
    if (screenChar == 'x' || screenChar == '$') {// Collision with explosion or monster
        if (!m_Levitate) {
            takeDamage();
        }
        return true;
    }
    if (screenChar == 'H' || screenChar == 'D' || screenChar == 'B'
        || screenChar == 'L' || screenChar == 'R') // Effect collision
        return true;
    return false;
}
//----------------------------------------------------------------------------------------------

void Player::receiveEffect(int effect)
{
    switch (effect) {
        case DAMAGE:
            takeDamage();
            break;
        case BOMB_INC:
            m_BombsCount++;
            break;
        case RADIUS_INC:
            m_BombRadius++;
            break;
        case HEAL:
            m_Health++;
            break;
        case LEVITATE:
            m_Levitate = true;
            startTimer(LEVITATE);
            break;
        case DETONATOR:
            m_Detonator = true;
            startTimer(DETONATOR);
        default:
            break;
    }
}
//----------------------------------------------------------------------------------------------

void Player::checkHealth()
{
    if (m_Health <= 0)
        m_Exist = false;
}
//----------------------------------------------------------------------------------------------
void Player::takeDamage()
{
    if ( m_Invulnerable )
        return;

    m_Health--;
    m_Invulnerable = true;
    startTimer(DAMAGE);
}
//----------------------------------------------------------------------------------------------

void Player::startTimer( int timerType )
{
    m_TimePoints[timerType] = std::chrono::steady_clock::now();
}
//----------------------------------------------------------------------------------------------

void Player::checkState()
{
    auto currTimePoint = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime{};
    if ( m_Invulnerable ) {
        elapsedTime = currTimePoint - m_TimePoints[0];
        if ( elapsedTime.count() >= 1 )
            m_Invulnerable = false;
    }
    if ( m_Levitate ) {
        elapsedTime = currTimePoint - m_TimePoints[1];
        if ( elapsedTime.count() >= 5 )
            m_Levitate = false;
    }

    if ( m_Detonator ) {
        elapsedTime = currTimePoint - m_TimePoints[2];
        if ( elapsedTime.count() >= 5 )
            m_Detonator = false;
    }
}
//----------------------------------------------------------------------------------------------


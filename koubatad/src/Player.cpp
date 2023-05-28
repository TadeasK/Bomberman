#include "Player.hpp"


Player::Player(int x, int y, WINDOW *window, int color, int speed, int bombRadius, int bombsCount,
               int bombTimer, int health) : Entity(x, y, window, speed) {
    m_Color = color;
    m_BombRadius = bombRadius;
    m_BombsCount = bombsCount;
    m_BombTimer = bombTimer;
    m_Health = health;
}

//----------------------------------------------------------------------------------------------
bool Player::drawObj() const {
    wattron(m_Window, COLOR_PAIR(m_Color));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(m_Color));
    return m_Exist;
}

//----------------------------------------------------------------------------------------------
void Player::move() {
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
    // TODO POSSIBLE BUG WITH THROW
    m_Dir = 0;
}

//----------------------------------------------------------------------------------------------
void Player::setMove(size_t dir) {
    checkBombs();
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
std::shared_ptr<Bomb> Player::placeBomb() {
    // TODO Throw at player pos + throw dist (method deciding face direction)
    if (m_BombsPlaced.size() >= m_BombsCount)
        return nullptr;

    // if ( !checkConstrains() )

    int bombX = m_X, bombY = m_Y; // + m_BombThrow
    auto bomb = std::make_shared<Bomb>(bombX, bombY, m_Window, m_BombTimer, m_BombRadius);
    m_BombsPlaced.push_back(bomb);
    return bomb;
}
//----------------------------------------------------------------------------------------------
void Player::checkBombs() {
    for ( auto bombIt = m_BombsPlaced.begin(); bombIt != m_BombsPlaced.end(); ) {
        if ( (*bombIt)->m_Exploded )
            bombIt = m_BombsPlaced.erase(bombIt);
        else
            ++bombIt;
    }
}
bool Player::moveUp() {
    if (!checkConstrains(m_X, m_Y - m_Speed))
        return false;
    m_Y -= m_Speed;
    return true;
}

//----------------------------------------------------------------------------------------------
bool Player::moveLeft() {
    if (!checkConstrains(m_X - m_Speed, m_Y))
        return false;
    m_X -= m_Speed;
    return true;
}

//----------------------------------------------------------------------------------------------
bool Player::moveRight() {
    if (!checkConstrains(m_X + m_Speed, m_Y))
        return false;
    m_X += m_Speed;
    return true;
}
//----------------------------------------------------------------------------------------------

bool Player::moveDown() {
    if (!checkConstrains(m_X, m_Y + m_Speed))
        return false;
    m_Y += m_Speed;
    return true;
}

//----------------------------------------------------------------------------------------------
int Player::getHealth() const {
    return m_Health;
}

//----------------------------------------------------------------------------------------------
bool Player::checkConstrains(int x, int y) {
    if (x < 0 || y < 0 || x > GAME_WINDOW_WIDTH || y > GAME_WINDOW_HEIGHT)
        return false;

    chtype screenObj = mvwinch(m_Window, y, x);
    chtype screenChar = screenObj & A_CHARTEXT;
    if ( screenChar == ' ')
        return true;
    else if ( screenChar == '#' || screenChar == 'X' )
        return false;
    return m_Levitate;
}

void Player::receiveEffect(int effect)
{
    switch (effect) {
        case EXPLOSION:
            m_Health--;
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
            break;
        case DETONATOR:
            m_Detonator = true;
        default:
            break;
    }
}


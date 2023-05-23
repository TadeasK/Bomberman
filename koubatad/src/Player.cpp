#include "Player.hpp"


Player::Player(int x, int y, WINDOW *window, int color, int speed, int bombRadius, int bombsCount, int bombThrow,
               int bombTimer, int health) : Entity(x, y, window, speed) {
    m_Color = color;
    m_BombRadius = bombRadius;
    m_BombsCount = bombsCount;
    m_BombThrow = bombThrow;
    m_BombTimer = bombTimer;
    m_Health = health;
}

//----------------------------------------------------------------------------------------------
void Player::drawObj() const {
    wattron(m_Window, COLOR_PAIR(m_Color));
    mvwprintw(m_Window, m_Y, m_X, "%c", m_Repr);
    wattroff(m_Window, COLOR_PAIR(m_Color));

}

//----------------------------------------------------------------------------------------------
void Player::move() {
    for (const auto &bomb: m_BombsPlaced)
        bomb.drawObj();

    switch (m_State) {
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
        case PLACE_BOMB:
            placeBomb();
            break;
        default:
            break;
    }
    m_State = 0;
}

//----------------------------------------------------------------------------------------------
void Player::setAction(size_t action) {
    switch (action) {
        case 'w':
        case KEY_UP:
            m_State = MOVE_UP;
            break;
        case 'a':
        case KEY_LEFT:
            m_State = MOVE_LEFT;
            break;
        case 's':
        case KEY_DOWN:
            m_State = MOVE_DOWN;
            break;
        case 'd':
        case KEY_RIGHT:
            m_State = MOVE_RIGHT;
            break;
        case ' ':
        case KEY_ENTER:
            m_State = PLACE_BOMB;
            break;
        default:
            break;
    }
}

//----------------------------------------------------------------------------------------------
bool Player::placeBomb() {
    // TODO Throw at player pos + throw dist (method deciding face direction)
    //      set bomb radius, add bombs placed
    if (m_BombsPlaced.size() >= m_BombsCount)
        return false;

    // if ( !checkConstrains() )

    int bombX = m_X, bombY = m_Y; // + m_BombThrow
    m_BombsPlaced.emplace_back(Bomb(bombX, bombY, m_Window, m_BombTimer, m_BombRadius));
    return true;
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
    switch (screenChar) {
        case ' ':
            return true;
        case '$':
            m_Health--;
            return false;
        default:
            return false;
    }
}


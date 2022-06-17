#include "GameManager.hpp"

GameManager::GameManager(bool multi, std::string &map)
        : Menu() {
    m_Multi = multi;
    m_MapPath = map;
    running = true;
    delwin(menuWindow);
    menuWidth = GAME_WINDOW_WIDTH;
    menuHeight = GAME_WINDOW_HEIGHT;
    menuWindow = newwin(menuHeight, menuWidth, m_HEIGHT / 2 - menuHeight / 2, m_WIDTH / 2 - menuWidth / 2);
    keypad(menuWindow, true);
    nodelay(menuWindow, true);
    generateMap();
}
//----------------------------------------------------------------------------------------------

void GameManager::runMenu() {
    int input;
    size_t x = 0;
    while (running) {
        box(menuWindow, x, x);
        wrefresh(menuWindow);
        refresh();

        input = readInput(x);

        input = static_cast<size_t>(input);
        takeAction(input);
        printStats();

        for (auto const &obj: m_Objects)
            obj->drawObj();

        for (auto const &entity: m_Entities)
            entity->move();

        if (input != ERR)
            werase(menuWindow);
    }
    // saveScore();
    cleanUp();
    delwin(menuWindow);
}

//----------------------------------------------------------------------------------------------

void GameManager::generateMap() {
    std::string objects = readConfig(m_MapPath);
    int index = 0;
    for (int i = 1; i < GAME_WINDOW_HEIGHT - 1; i++) {
        for (int j = 1; j < GAME_WINDOW_WIDTH - 1; j++) {
            switch (objects[index]) {
                case '0':
                    break;
                case '1':
                    createWall(j, i);
                    break;
                case '2':
                    createCrate(j, i, false);
                    break;
                case '3':
                    createCrate(j, i, true);
                    break;
                case '4':
                    createEnemy(j, i);
                    break;
                case '5':
                    createPlayer1(j, i);
                    break;
                case '6':
                    createPlayer2(j, i);
                    break;
                default:
                    throw "Content of file " + m_MapPath + " might be corrupted.";
            }
            index++;
        }
    }
    if ( (m_Player2 == nullptr && m_Multi )|| m_Player1 == nullptr )
        throw "Content of file " + m_MapPath + " might be corrupted.";
}

//----------------------------------------------------------------------------------------------

int GameManager::readInput(size_t &currSelect) {
    int input = wgetch(menuWindow);

    if (input == EOT || input == ETX) { // Check if user pressed ctrl+C or ctrl+D
        running = false;
        return -1;
    }

    return input;
}
//----------------------------------------------------------------------------------------------

void GameManager::takeAction(size_t action) {
    if (action == ENTER)
        action = KEY_ENTER;
    if (action == 'w' || action == 'a' || action == 's' || action == 'd' || action == ' ')
        m_Player1->setAction(action);
    if (m_Multi) {
        if (action == KEY_UP || action == KEY_LEFT || action == KEY_RIGHT || action == KEY_DOWN || action == KEY_ENTER)
            m_Player2->setAction(action);
    }
}

//----------------------------------------------------------------------------------------------
void GameManager::printStats() {
    mvprintw((m_HEIGHT / 2 - menuHeight / 2) - 1, m_WIDTH / 2 - menuWidth / 2,
             "%s: %d", "P1 HEALTH", m_Player1->getHealth());

    if (!m_Multi)
        mvprintw((m_HEIGHT / 2 - menuHeight / 2) - 2, m_WIDTH / 2 - 3,
                 "%s: %d", "SCORE", m_Score);

    if (m_Multi)
        mvprintw((m_HEIGHT / 2 + menuHeight / 2) + 1, m_WIDTH / 2 - menuWidth / 2,
                 "%s: %d", "P2 HEALTH", m_Player2->getHealth());
}

//----------------------------------------------------------------------------------------------

std::string GameManager::readConfig(const std::string &path) {
    std::ifstream inFile(path);
    if (!inFile.is_open() || !inFile.good())
        throw "Couldn't open file: '" + path + "'.";

    return parseFile(inFile);
}

//----------------------------------------------------------------------------------------------

std::string GameManager::parseFile(std::ifstream &file) {
    std::string line;
    std::string final;
    while (std::getline(file, line)) {
        final.append(line);
    }
    if ( final.length() != (size_t)((GAME_WINDOW_WIDTH-2)*(GAME_WINDOW_HEIGHT-2)) )
        throw "Content of file '" + m_MapPath + "' might be corrupted.";
    return final;
}
//----------------------------------------------------------------------------------------------

void GameManager::createWall(int x, int y) {
    m_Objects.emplace_back(std::make_shared<Wall>(x, y, menuWindow));
}

//----------------------------------------------------------------------------------------------
void GameManager::createCrate(int x, int y, bool isFull) {
    m_Objects.emplace_back(std::make_shared<Crate>(x, y, menuWindow, isFull));
}

//----------------------------------------------------------------------------------------------
void GameManager::createEnemy(int x, int y) {
    if ( !m_Multi) {
        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(x, y, menuWindow, 1);
        m_Objects.emplace_back(enemy);
        m_Entities.emplace_back(enemy);
    }
}

//----------------------------------------------------------------------------------------------
void GameManager::createPlayer1(int x, int y) {
    if ( m_Player1 == nullptr ) {
        m_Player1 = std::make_shared<Player>(x, y, menuWindow);
        m_Objects.push_back(m_Player1);
        m_Entities.push_back(m_Player1);
    }
    else
        throw "Content of file '" + m_MapPath + "' might be corrupted.";
}

//----------------------------------------------------------------------------------------------
void GameManager::createPlayer2(int x, int y) {
    if (!m_Multi)
        return;
    if ( m_Player2 == nullptr ) {
        m_Player2 = std::make_shared<Player>(x, y, menuWindow, 5);
        m_Objects.push_back(m_Player2);
        m_Entities.push_back(m_Player2);
    }
    else
        throw "Content of file '" + m_MapPath + "' might be corrupted.";
}
//----------------------------------------------------------------------------------------------

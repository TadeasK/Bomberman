#include "GameManager.hpp"

GameManager::GameManager(bool multi, std::string &map, std::string &score, bool test) : Menu()
{
    m_Multi = multi;
    m_Test = test;
    m_MapPath = map;
    m_ScorePath = score;
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

// TODO collisions, damage
void GameManager::runMenu()
{
    int input;
    int x = 0;
    m_StartTime = std::chrono::steady_clock::now();
    const std::chrono::microseconds frameDelay(static_cast<int>(1000.0 / 30.0));

    while (running) {
        auto start = std::chrono::steady_clock::now();
        box(menuWindow, x, x);
        wrefresh(menuWindow);
        refresh();

        input = readInput(x);
        takeAction(input);
        printStats();

        for (auto bombIt = m_Bombs.begin(); bombIt != m_Bombs.end();) {
            (*bombIt)->action();
            if ((*bombIt)->m_Exploded) {
                bombIt = m_Bombs.erase(bombIt);
                explodeBomb(*bombIt);
            }
            else
                ++bombIt;
        }

        for (auto const &spec: m_Special) {
            int status = spec->update();
            if (status == 1)
                handleCollision(spec);
        }

        for (auto obj = m_Objects.begin(); obj != m_Objects.end();) {
            if (!(*obj)->drawObj()) { // Object was destroyed/killed
                if ((*obj) == m_Player1) {
                    if (m_Multi)
                        m_Player1Winner = false;
                    running = false;
                    break;
                }
                if ((*obj) == m_Player2) {
                    m_Player1Winner = true;
                    running = false;
                    break;

                if (checkEntity((*obj))) // Must be Enemy
                    m_Score += 100;

                if (checkSpecial((*obj))) // Must be Special
                    m_Score += 50;

                obj = m_Objects.erase(obj);
            }
            else
                ++obj;
        }

        for (auto const &entity: m_Entities)
            entity->move();

        if (input != ERR)
            werase(menuWindow);

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto delay = frameDelay - elapsed;
        if (delay > std::chrono::milliseconds::zero())
            std::this_thread::sleep_for(delay);
    }
    werase(menuWindow);
    wrefresh(menuWindow);
    cleanUp();
    if (input == -2) {
        delwin(menuWindow);
        return;
    }

    if (m_Multi)
        displayWinner();
    else
        saveScore();
    delwin(menuWindow);
}

//----------------------------------------------------------------------------------------------
// TODO add Testing mode
void GameManager::generateMap()
{
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
                    if (m_Test)
                        createBonus({j,i}, Object::EFFECT::LEVITATE);
                    break;
                case '7':
                    if (m_Test)
                        createBonus({j,i}, Object::EFFECT::DETONATOR);
                    break;
                case '8':
                    if (m_Test)
                        createBonus({j,i}, Object::EFFECT::BOMB_INC);
                    break;
                case '9':
                    if (m_Test)
                        createBonus({j,i}, Object::EFFECT::RADIUS_INC);
                    break;
                case 'x':
                    if (m_Test)
                        createBonus({j,i}, Object::EFFECT::HEAL);
                    break;
                default:
                    throw "Content of file " + m_MapPath + " might be corrupted.";
            }
            index++;
        }
    }
    if ((m_Player2 == nullptr && m_Multi) || m_Player1 == nullptr)
        throw "Content of file " + m_MapPath + " might be corrupted.";
}

//----------------------------------------------------------------------------------------------

int GameManager::readInput(int &currSelect)
{
    int input = wgetch(menuWindow);

    if (input == EOT || input == ETX) { // Check if user pressed ctrl+C or ctrl+D
        running = false;
        return -1;
    }

    return input;
}
//----------------------------------------------------------------------------------------------

void GameManager::takeAction(int action)
{
    if (action == ENTER)
        action = KEY_ENTER;
    if (action == 'w' || action == 'a' || action == 's' || action == 'd')
        m_Player1->setMove(action);
    if (action == ' ') {
        auto bomb = m_Player1->placeBomb();
        if (bomb != nullptr) {
            m_Objects.push_back(bomb);
            m_Bombs.push_back(bomb);
        }
    }
    if (m_Multi) {
        if (action == KEY_UP || action == KEY_LEFT || action == KEY_RIGHT || action == KEY_DOWN)
            m_Player2->setMove(action);
        if (action == KEY_ENTER) {
            auto bomb = m_Player2->placeBomb();
            if (bomb != nullptr) {
                m_Objects.push_back(bomb);
                m_Bombs.push_back(bomb);
            }
        }
    }
}

//----------------------------------------------------------------------------------------------
void GameManager::printStats()
{
    mvprintw((m_HEIGHT / 2 - menuHeight / 2) - 1, m_WIDTH / 2 - menuWidth / 2, "%s: %d", "P1 HEALTH",
             m_Player1->getHealth());

    if (!m_Multi)
        mvprintw((m_HEIGHT / 2 - menuHeight / 2) - 2, m_WIDTH / 2 - menuWidth / 2, "%s: %d", "SCORE", m_Score);

    if (m_Multi)
        mvprintw((m_HEIGHT / 2 + menuHeight / 2) + 1, m_WIDTH / 2 - menuWidth / 2, "%s: %d", "P2 HEALTH",
                 m_Player2->getHealth());


    mvprintw((m_HEIGHT / 2 - menuHeight / 2) - 3, m_WIDTH / 2 - menuWidth / 2, "%s: %.2f", "TIME", getElapsedTime());
}

//----------------------------------------------------------------------------------------------

std::string GameManager::readConfig(const std::string &path)
{
    std::ifstream inFile(path);
    if (!inFile.is_open() || !inFile.good())
        throw "Couldn't open file: '" + path + "'.";

    return parseFile(inFile);
}

//----------------------------------------------------------------------------------------------

std::string GameManager::parseFile(std::ifstream &file)
{
    std::string line;
    std::string final;
    while (std::getline(file, line)) {
        final.append(line);
    }
    if (final.length() != (size_t) ((GAME_WINDOW_WIDTH - 2) * (GAME_WINDOW_HEIGHT - 2)))
        throw "Content of file '" + m_MapPath + "' might be corrupted.";
    return final;
}
//----------------------------------------------------------------------------------------------

void GameManager::createWall(int x, int y)
{
    m_Objects.emplace_back(std::make_shared<Wall>(x, y, menuWindow));
}

//----------------------------------------------------------------------------------------------
void GameManager::createCrate(int x, int y, bool isFull)
{
    m_Objects.emplace_back(std::make_shared<Crate>(x, y, menuWindow, isFull));
}

//----------------------------------------------------------------------------------------------
void GameManager::createEnemy(int x, int y)
{
    if (!m_Multi) {
        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(x, y, menuWindow, 1);
        m_Objects.emplace_back(enemy);
        m_Entities.emplace_back(enemy);
    }
}

//----------------------------------------------------------------------------------------------
void GameManager::createPlayer1(int x, int y)
{
    if (m_Player1 == nullptr) {
        if ( m_Test )
            m_Player1 = std::make_shared<Player>(coord.first, coord.second, menuWindow, 4, 1, 3, 3, 3);
        else
            m_Player1 = std::make_shared<Player>(coord.first, coord.second, menuWindow);
        m_Objects.push_back(m_Player1);
        m_Entities.push_back(m_Player1);
    }
    else
        throw "Content of file '" + m_MapPath + "' might be corrupted.";
}

//----------------------------------------------------------------------------------------------
void GameManager::createPlayer2(int x, int y)
{
    if (!m_Multi)
        return;
    if (m_Player2 == nullptr) {
        m_Player2 = std::make_shared<Player>(x, y, menuWindow, 5);
        m_Objects.push_back(m_Player2);
        m_Entities.push_back(m_Player2);
    }
    else
        throw "Content of file '" + m_MapPath + "' might be corrupted.";
}

//----------------------------------------------------------------------------------------------
double GameManager::getElapsedTime() const
{
    auto currTimePoint = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currTimePoint - m_StartTime;
    return elapsedTime.count();
}

//----------------------------------------------------------------------------------------------
void GameManager::explodeBomb(std::shared_ptr<Bomb> &bomb)
{
    auto explosion = bomb->explode();
    for (const auto &x: explosion) {
        int status = x->collision();
        if (status == -1) {
            continue;
        }
        else if (status == 1) {
            handleCollision(x);
            m_Special.emplace_back(x);
            m_Objects.emplace_back(x);
        }
        else {
            m_Special.emplace_back(x);
            m_Objects.emplace_back(x);
        }
    }

    for (auto objIt = m_Objects.begin(); objIt != m_Objects.end();) {
        if (*objIt == bomb)
            objIt = m_Objects.erase(objIt);
        else
            ++objIt;
    }
}

//----------------------------------------------------------------------------------------------
void GameManager::handleCollision(const std::shared_ptr<Special> &special)
{
    for (auto &obj: m_Objects) {
        if (obj->getPosition() == special->getPosition())
            obj->receiveEffect(special->giveEffect());
    }
}
//----------------------------------------------------------------------------------------------

bool GameManager::checkEntity(const std::shared_ptr<Object> &obj)
{
    for (auto entity = m_Entities.begin(); entity != m_Entities.end();) {
        if (*entity == obj) {
            m_Entities.erase(entity);
            return true;
        }
        ++entity;
    }
    return false;
}
//----------------------------------------------------------------------------------------------

bool GameManager::checkSpecial(const std::shared_ptr<Object> &obj)
{
    bool ret = false;
    for (auto spec = m_Special.begin(); spec != m_Special.end();) {
        if (*spec == obj) {
            if ((*spec)->giveEffect() != 0)
                ret = true;
            m_Special.erase(spec);
            return ret;
        }
        ++spec;
    }
    return false;
}

//----------------------------------------------------------------------------------------------
void GameManager::displayWinner()
{
    int width = 30, height = 10;
    std::string message = "WINNER IS:";
    std::string winner = m_Player1Winner ? "PLAYER 1" : "PLAYER 2";
    std::string hint = "Press ENTER to continue";
    auto winnerWindow = newwin(height, width, m_HEIGHT / 2 - height / 2,
                               m_WIDTH / 2 - width / 2);

    mvwprintw(winnerWindow, 2, (width / 2 - message.length() / 2), "%s", message.c_str());
    wattron(winnerWindow, COLOR_PAIR(3) | A_BLINK);
    mvwprintw(winnerWindow, 3, (width / 2 - winner.length() / 2), "%s", winner.c_str());
    wattroff(winnerWindow, COLOR_PAIR(3) | A_BLINK);
    mvwprintw(winnerWindow, 6, (width / 2 - hint.length() / 2), "%s", hint.c_str());

    box(winnerWindow, 0, 0);
    int input;
    while (true) {
        input = wgetch(winnerWindow);
        if (input == ENTER || input == EOT || input == ETX)
            break;
    }
    wrefresh(winnerWindow);
    delwin(winnerWindow);
}

//----------------------------------------------------------------------------------------------
void GameManager::saveScore()
{

    auto scores = readScoreFile(m_ScorePath);
    int map = m_MapPath.back() - '0';
    if (scores.count(map) != 0)
        if (scores[map].second > m_Score) {
            displayErr("You DIED!", "");
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            return;
        }

    int width = 30, height = 10;
    std::string message = "NEW HIGH SCORE!";
    std::string namePrompt = "Enter your name:";
    std::string hint = "Press ENTER to continue";
    auto scoreWindow = newwin(height, width, m_HEIGHT / 2 - height / 2,
                              m_WIDTH / 2 - width / 2);

    mvwprintw(scoreWindow, 2, (width / 2 - message.length() / 2), "%s", message.c_str());
    mvwprintw(scoreWindow, 3, (width / 2 - namePrompt.length() / 2), "%s", namePrompt.c_str());
    mvwprintw(scoreWindow, 6, (width / 2 - hint.length() / 2), "%s", hint.c_str());

    box(scoreWindow, 0, 0);
    echo();
    int input;
    std::string name = "";
    wmove(scoreWindow, 4, 2);
    while (true) {
        input = wgetch(scoreWindow);
        if (input == ENTER || input == EOT || input == ETX)
            break;
        if (name.length() > 24) {
            noecho();
            continue;
        }
        name += input;
    }

    scores[map] = {name, m_Score};
    writeScore(scores);

    noecho();
    wrefresh(scoreWindow);
    delwin(scoreWindow);
}

//----------------------------------------------------------------------------------------------
void GameManager::writeScore(const std::map<int, std::pair<std::string, int>> &scores)
{
    std::ofstream oFile(m_ScorePath);
    for (const auto &line: scores) {
        oFile << line.first << ':' << line.second.first << ':' << line.second.second << "\n";
    }
}
//----------------------------------------------------------------------------------------------

#include "GameManager.hpp"

GameManager::GameManager(bool multi, std::string &map, std::string &score, std::string &conf, bool test) : Menu()
{
    m_Multi = multi;
    m_Test = test;
    m_MapPath = map;
    m_ScorePath = score;
    m_ConfigPath = conf;
    running = true;
    delwin(menuWindow);
    menuWidth = GAME_WINDOW_WIDTH;
    menuHeight = GAME_WINDOW_HEIGHT;
    menuWindow = newwin(menuHeight, menuWidth, m_HEIGHT / 2 - menuHeight / 2, m_WIDTH / 2 - menuWidth / 2);
    keypad(menuWindow, true);
    nodelay(menuWindow, true);
    generateMap();
    readConfig();
}
//----------------------------------------------------------------------------------------------

// TODO collisions, damage
void GameManager::runMenu()
{
    int input = -1;
    int x = 0;
    m_StartTime = std::chrono::steady_clock::now();
    const std::chrono::microseconds frameDelay(static_cast<int>(1000.0 / 30.0));

    while (running) {
        auto start = std::chrono::steady_clock::now();
        box(menuWindow, 0, 0);
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
                }

                if (checkEntity((*obj))) // Must be Enemy
                    m_Score += m_Config.m_MonsterScore;
                else if (checkSpecial((*obj))) {// Must be Special
                    // TODO Gives score even if it despawns probably
                    m_Score += m_Config.m_BonusScore;
                }
                else {
                    createBonus(std::pair<int, int>((*obj)->getPosition()));
                }
                obj = m_Objects.erase(obj);
            }
            else
                ++obj;
        }

        for (auto const &spec: m_Special) {
            int status = spec->update();
            if (status == 1)
                handleCollision(spec);
        }

        if ( m_Entities.size() <= 1 ) { // Only player left
            running = false;
            m_Player1Winner = true;
            break;
        }

        for (auto const &entity: m_Entities) {
            entity->move(m_Player1->getPosition());
            if ( entity->getPosition() == m_Player1->getPosition() && entity != m_Player1 )
                m_Player1->receiveEffect(Object::EFFECT::DAMAGE);
        }


        if ( m_Entities.size() <= 1 && !m_Test) { // Only player left
            running = false;
            m_Player1Winner = true;
            break;
        }

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
void GameManager::generateMap()
{
    std::string objects = readMapFile(m_MapPath);
    int index = 0;
    for (int i = 1; i < GAME_WINDOW_HEIGHT - 1; i++) {
        for (int j = 1; j < GAME_WINDOW_WIDTH - 1; j++) {
            switch (objects[index]) {
                case '0':
                    break;
                case '1':
                    createWall({j, i});
                    break;
                case '2':
                    createCrate({j, i});
                    break;
                case '3':
                    createEnemy({j, i});
                    break;
                case '4':
                    createPlayer1({j, i});
                    break;
                case '5':
                    createPlayer2({j, i});
                    break;
                case '6':
                    if (m_Test)
                        createBonus({j, i}, Object::EFFECT::LEVITATE);
                    break;
                case '7':
                    if (m_Test)
                        createBonus({j, i}, Object::EFFECT::DETONATOR);
                    break;
                case '8':
                    if (m_Test)
                        createBonus({j, i}, Object::EFFECT::BOMB_INC);
                    break;
                case '9':
                    if (m_Test)
                        createBonus({j, i}, Object::EFFECT::RADIUS_INC);
                    break;
                case 'x':
                    if (m_Test)
                        createBonus({j, i}, Object::EFFECT::HEAL);
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
        return -2;
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

std::string GameManager::readMapFile(const std::string &path)
{
    std::ifstream inFile(path);
    if (!inFile.is_open() || !inFile.good())
        throw "Couldn't open file: '" + path + "'.";

    return parseMapFile(inFile);
}

//----------------------------------------------------------------------------------------------

std::string GameManager::parseMapFile(std::ifstream &file)
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

void GameManager::createWall(std::pair<int, int> coord)
{
    m_Objects.emplace_back(std::make_shared<Wall>(coord.first, coord.second, menuWindow));
}

//----------------------------------------------------------------------------------------------
void GameManager::createCrate(std::pair<int, int> coord)
{
    m_Objects.emplace_back(std::make_shared<Crate>(coord.first, coord.second, menuWindow));
}

//----------------------------------------------------------------------------------------------
void GameManager::createEnemy(std::pair<int, int> coord)
{
    if (!m_Multi) {
        std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(coord.first, coord.second, menuWindow, 1);
        m_Objects.emplace_back(enemy);
        m_Entities.emplace_back(enemy);
    }
}

//----------------------------------------------------------------------------------------------
void GameManager::createPlayer1(std::pair<int, int> coord)
{
    if (m_Player1 == nullptr) {
        if (m_Test)
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
void GameManager::createPlayer2(std::pair<int, int> coord)
{
    if (!m_Multi)
        return;
    if (m_Player2 == nullptr) {
        m_Player2 = std::make_shared<Player>(coord.first, coord.second, menuWindow, 5);
        m_Objects.push_back(m_Player2);
        m_Entities.push_back(m_Player2);
    }
    else
        throw "Content of file '" + m_MapPath + "' might be corrupted.";
}

//----------------------------------------------------------------------------------------------
void GameManager::createBonus(std::pair<int, int> coord, int bonus)
{
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    std::vector<double> probabilities{m_Config.m_LevitateChance, m_Config.m_DetonatorChance, m_Config.m_BombChance,
                                      m_Config.m_RadiusChance, m_Config.m_HealChance};
    double randomNumber;
    if (bonus == 0) {
        randomNumber = distribution(gen);
        if ( randomNumber > m_Config.m_DropChance) // Drop didn't happen
            return;
        // Drop happened, choose effect
        randomNumber = distribution(gen);
        double totalProbability = 0.0;
        int i = 1;
        for (const auto &x: probabilities) {
           totalProbability += x;
           if ( randomNumber <= totalProbability ) {
               bonus = i;
               break;
           }
           ++i;
        }
    }

    std::shared_ptr<Special> special = nullptr;
    switch (bonus) {
        case Object::EFFECT::LEVITATE:
            special = std::make_shared<BuffLevitate>(coord.first, coord.second, menuWindow);
            break;
        case Object::EFFECT::DETONATOR:
            special = std::make_shared<BuffDetonator>(coord.first, coord.second, menuWindow);
            break;
        case Object::EFFECT::BOMB_INC:
            special = std::make_shared<BuffBomb>(coord.first, coord.second, menuWindow);
            break;
        case Object::EFFECT::RADIUS_INC:
            special = std::make_shared<BuffRadius>(coord.first, coord.second, menuWindow);
            break;
        case Object::EFFECT::HEAL:
            special = std::make_shared<BuffHeal>(coord.first, coord.second, menuWindow);
            break;
        default:
            break;
    }
    if (special != nullptr) {
        m_Objects.push_back(special);
        m_Special.push_back(special);
    }
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
    bool limitUp = false, limitDown = false, limitLeft = false, limitRight = false;
    auto center = explosion.front()->getPosition();
    for (const auto &x: explosion) {
        int status = x->collision();
        auto pos = x->getPosition();
        // Check if boundary was already encountered in given axis way
        if ( pos.first < center.first ) {
            if ( limitLeft )
                continue;
        }
        else if ( pos.first > center.first ) {
            if ( limitRight )
                continue;
        }
        else if ( pos.second < center.second ) {
            if ( limitUp )
                continue;
        }
        else if ( pos.second > center.second ) {
            if ( limitDown )
                continue;
        }

        if (status == 0 ) { // Free movement
            m_Special.emplace_back(x);
            m_Objects.emplace_back(x);
            continue;
        }
        else if (status == 1) { // Hit non-crate
            handleCollision(x);
            m_Special.emplace_back(x);
            m_Objects.emplace_back(x);
        }
        // Set boundary in given axis way
        if ( pos.first < center.first )
            limitLeft = true;
        else if ( pos.first > center.first )
            limitRight = true;
        else if ( pos.second < center.second )
            limitUp = true;
        else if ( pos.second > center.second )
            limitDown = true;
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
        if ( obj == m_Player1 && special->giveEffect() != Object::EFFECT::DAMAGE)
            m_Score += m_Config.m_BonusScore;
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
            if ((*spec)->giveEffect() != Object::EFFECT::DAMAGE)
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
    if ( m_Player1Winner )
        displayErr("You WIN!", "Good Job!");
    else
        displayErr("You DIED!", "Better luck next time!");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    if (scores.count(map) != 0) {
        if (scores[map].second > m_Score)
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
void GameManager::readConfig()
{
    std::vector<std::pair<std::string, double>> values;
    std::ifstream conf(m_ConfigPath);
    if ( !conf )
        return;
    std::string line;
    std::string part;
    std::string field;
    double value;
    while( conf >> line ) {
        std::stringstream ss(line);
        for ( int i = 0; i < 2; ++i ) {
            std::getline(ss, part, ':');
            if ( i == 0 )
                field = part;
            else
            value = atof(part.c_str());
        }
        values.emplace_back(field,value);
    }
    parseConfig(values);
}
//----------------------------------------------------------------------------------------------

void GameManager::parseConfig(std::vector<std::pair<std::string, double>> &values)
{
    double combinedChance = 0;
    for ( const auto &x: values) {
        combinedChance += x.second;
        if ( x.first == "drop" ) {
            combinedChance -= x.second;
            if ( x.second > 0 && x.second <= 1.0)
                m_Config.m_DropChance = x.second;
        }
        else if ( x.first == "levitate" ) {
            if ( x.second > 0 && x.second <= 1.0)
                m_Config.m_LevitateChance = x.second;
        }
        else if ( x.first == "detonator" ) {
            if ( x.second > 0 && x.second <= 1.0)
                m_Config.m_DetonatorChance = x.second;
        }
        else if ( x.first == "bomb" ) {
            if ( x.second > 0 && x.second <= 1.0)
                m_Config.m_BombChance = x.second;
        }
        else if ( x.first == "radius" ) {
            if ( x.second > 0 && x.second <= 1.0)
                m_Config.m_RadiusChance = x.second;
        }
        else if ( x.first == "heal" ) {
            if ( x.second > 0 && x.second <= 1.0)
                m_Config.m_HealChance = x.second;
        }
        else if ( x.first == "monster" ) {
            combinedChance -= x.second;
            m_Config.m_MonsterScore = x.second;
        }
        else if ( x.first == "bonus" ) {
            combinedChance -= x.second;
            m_Config.m_BonusScore = x.second;
        }
        else
            continue;
    }
    if ( combinedChance != 1.0 ) {
        m_Config.m_RadiusChance = m_Config.m_DetonatorChance = m_Config.m_BombChance = \
            m_Config.m_LevitateChance = m_Config.m_HealChance = 0.2;
        return;
    }
}
//----------------------------------------------------------------------------------------------

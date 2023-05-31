#include "ScoreMenu.hpp"

ScoreMenu::ScoreMenu(const std::string &scorePath)
        : Menu()
{
    m_Name = "Hall Of Fame";
    menuItems = {
            "Back"
    };
    m_Scores = readScoreFile(scorePath);
}
//----------------------------------------------------------------------------------------------

void ScoreMenu::takeAction(int currSelect)
{
    switch (currSelect) {
        case BACK:
            running = false;
            cleanUp();
            break;
    }
}

//----------------------------------------------------------------------------------------------
void ScoreMenu::displayCustom()
{
    std::string head = "MAP. NAME : SCORE";
    mvwprintw(menuWindow, 4, (menuWidth / 2 - head.length() / 2),
              "%s", head.c_str());

    std::ostringstream oss;
    int i = 5;
    for (const auto &x: m_Scores) {
        oss << x.first << ". " << x.second.first << " : " << x.second.second;
        mvwprintw(menuWindow, i, (menuWidth / 2 - oss.str().length() / 2),
                  "%s", oss.str().c_str());
        oss.str("");
        ++i;
    }
}
//----------------------------------------------------------------------------------------------

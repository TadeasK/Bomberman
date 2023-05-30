#include "MainMenu.hpp"

MainMenu::MainMenu()
        : Menu()
{
    running = true;
    m_Name = "Main menu";

    menuItems = {
            "Start game",
            "Best Scores",
            "Controls",
            "Quit"
    };
}

//----------------------------------------------------------------------------------------------

void MainMenu::runGame()
{
    GameMenu gameMenu;
    gameMenu.runMenu();
}

//----------------------------------------------------------------------------------------------

void MainMenu::controls()
{
    OptionsMenu optionsMenu;
    optionsMenu.runMenu();
}

//----------------------------------------------------------------------------------------------
void MainMenu::showLeaderboard()
{
    ScoreMenu scoreMenu("assets/scores.txt");
    scoreMenu.runMenu();
}

//----------------------------------------------------------------------------------------------

void MainMenu::takeAction(int currSelect)
{
    switch (currSelect) {
        case START_GAME:
            cleanUp();
            runGame();
            break;
        case BEST_SCORES:
            cleanUp();
            showLeaderboard();
            break;
        case CONTROLS:
            cleanUp();
            controls();
            break;
        case QUIT:
            running = false;
            break;
        default:
            break;
    }
}
//----------------------------------------------------------------------------------------------



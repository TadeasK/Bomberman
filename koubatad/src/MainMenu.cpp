#include "MainMenu.hpp"

MainMenu::MainMenu()
    : Menu()
{
    initNcurses();

    running = true;
    m_Name = "Main menu";
    getmaxyx(stdscr,m_WIDTH,m_HEIGHT);
    menuHeight = m_HEIGHT / 2;
    menuWidth = m_WIDTH / 2;
    menuWindow = newwin(menuHeight, menuWidth, m_HEIGHT / 4, m_WIDTH / 4);
    keypad(menuWindow, true);

    menuItems = {
            "Start game",
            "Controls",
            "Quit"
    };
}

//----------------------------------------------------------------------------------------------

void MainMenu::initNcurses()
{
    initscr(); // Initialize window
    if ( !has_colors() ) {
        endwin();
        throw "Your terminal doesn't support colors, which is required to run this game.";
    }
    start_color(); // Initialize color mode
    initColors(); // Set color pairs

    cbreak();
    raw(); // Turn of line buffering
    keypad(stdscr, TRUE); // Activate special keys (arrow, F1...)
    noecho(); // Don't repeat input
    curs_set(0); // Make the cursor invisible

    getmaxyx(stdscr, m_HEIGHT, m_WIDTH); // Read window parameters
    // Check if terminal has sufficient dimensions
    if ( m_HEIGHT < MIN_HEIGHT || m_WIDTH < MIN_WIDTH ) {
        endwin();
        throw "Your terminal is too small. Minimum dimensions of terminal are: "
              + std::to_string(MIN_WIDTH) + " : " + std::to_string(MIN_HEIGHT);
    }
}

//----------------------------------------------------------------------------------------------


void MainMenu::initColors()
{
    init_pair(1, COLOR_RED, COLOR_BLACK); // Placed bomb, Wall color
    init_pair(2, COLOR_RED, COLOR_YELLOW); // Explosion color
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // Specials color
    init_pair(4, COLOR_GREEN, COLOR_BLACK); // Player color
    init_pair(5, COLOR_BLUE, COLOR_BLACK); // Player2 color
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK); // Hint color, Crate color
    init_pair(7, COLOR_YELLOW, COLOR_BLACK); // Enemy color
}

//----------------------------------------------------------------------------------------------

void MainMenu::runGame()
{
    GameMenu game;
    game.runMenu();
}

//----------------------------------------------------------------------------------------------

void MainMenu::options()
{
    OptionsMenu optionsMenu;
    optionsMenu.runMenu();
}

//----------------------------------------------------------------------------------------------

void MainMenu::takeAction(size_t currSelect)
{
    switch (currSelect) {
        case START_GAME:
            cleanUp();
            runGame();
            break;
        case CONTROLS:
            cleanUp();
            options();
            break;
        case QUIT:
            running = false;
            break;
        default:
            break;
    }
}

//----------------------------------------------------------------------------------------------



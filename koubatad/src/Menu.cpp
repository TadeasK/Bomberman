#include "Menu.hpp"

Menu::Menu()
{
    initNcurses();
    running = true;
    getmaxyx(stdscr,m_HEIGHT,m_WIDTH);
    menuHeight = m_HEIGHT / 2;
    menuWidth = m_WIDTH / 2;
    menuWindow = newwin(menuHeight, menuWidth, m_HEIGHT / 4, m_WIDTH / 4);
    keypad(menuWindow, true);
}

//----------------------------------------------------------------------------------------------

void Menu::initNcurses()
{
    initscr(); // Initialize window
    if ( !has_colors() ) {
        endwin();
        throw "Your terminal doesn't support colors, which is required to run this game.";
    }
    start_color(); // Initialize color mode
    initColors(); // Set color pairs

    cbreak();
    raw(); // Turn off line buffering
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

void Menu::initColors()
{
    init_pair(1, COLOR_RED, COLOR_MAGENTA); // Placed bomb, Wall color
    init_pair(8, COLOR_RED, COLOR_BLACK); // Placed bomb
    init_pair(2, COLOR_RED, COLOR_YELLOW); // Explosion color
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // Specials color
    init_pair(4, COLOR_GREEN, COLOR_BLACK); // Player color
    init_pair(5, COLOR_BLUE, COLOR_BLACK); // Player2 color
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK); // Hint color, Crate color
    init_pair(7, COLOR_YELLOW, COLOR_BLACK); // Enemy color
}

//----------------------------------------------------------------------------------------------

void Menu::runMenu()
{
    int input;
    size_t currSelect = 0;

    while (running) {
        if ( refreshWindow() )
            displayErr(sizeErrMsg, "");

        displayName();
        displayHelp();
        printMenuItems( currSelect );
        refresh();
        input = readInput( currSelect);

        if ( input == KEY_ENTER || input == ENTER ) // KEY_ENTER does not work for some reason
            takeAction (currSelect);
    }
    delwin(menuWindow);
    endwin();
}

//----------------------------------------------------------------------------------------------

int Menu::readInput(size_t& currSelect)
{
    int input = wgetch(menuWindow);

    if ( input == EOT || input == ETX ) { // Check if user pressed ctrl+C or ctrl+D
        running = false;
        return -1;
    }

    if ( input == KEY_UP || input == 'w' ) {
        if (currSelect == 0)
            currSelect = menuItems.size() - 1;
        else
            currSelect--;
    }
    else if ( input == KEY_DOWN || input == 's' ) {
        if ( currSelect == menuItems.size()-1)
            currSelect = 0;
        else
            currSelect++;
    }
    return input;
}

//----------------------------------------------------------------------------------------------

void Menu::printMenuItems( size_t currSelect )
{
    for ( size_t i = 0; i < menuItems.size(); i++) { // Prints the menu and highlights current choice
        if ( i == currSelect )
            wattron(menuWindow, A_STANDOUT);
        if ( i == menuItems.size() - 1 ) {
            mvwprintw(menuWindow,
                      (menuHeight - 4),
                      (menuWidth / 2 - menuItems[i].length() / 2),
                      "%s", menuItems[i].c_str());
        }
        else {
            mvwprintw(menuWindow,
                      (menuHeight / 2 - menuItems.size() / 2 + i),
                      (menuWidth / 2 - menuItems[i].length() / 2),
                      "%s", menuItems[i].c_str());
        }
        wattroff(menuWindow, A_STANDOUT);
    }
}

//----------------------------------------------------------------------------------------------

void Menu::displayHelp()
{
    wattron(menuWindow, COLOR_PAIR(6));
    mvwprintw(menuWindow, menuHeight - 2, (menuWidth / 2 - hintMsg.length() / 2), "%s", hintMsg.c_str());
    wattroff(menuWindow, COLOR_PAIR(6));
}

//----------------------------------------------------------------------------------------------

void Menu::displayErr( const std::string& errMsg, const std::string& additionalInfo )
{
    wattron(stdscr, COLOR_PAIR(1));
    mvwprintw(stdscr,2, (m_WIDTH / 2 - errMsg.length() / 2), "%s", errMsg.c_str());
    mvwprintw(stdscr,3, (m_WIDTH / 2 - additionalInfo.length() / 2), "%s", additionalInfo.c_str());
    wattroff(stdscr, COLOR_PAIR(1));
}

//----------------------------------------------------------------------------------------------

void Menu::displayName()
{
    wattron(menuWindow, COLOR_PAIR(5) | A_UNDERLINE);
    mvwprintw(menuWindow, 3, (menuWidth / 2 - m_Name.length() / 2), "%s", m_Name.c_str());
    wattroff(menuWindow, COLOR_PAIR(5) | A_UNDERLINE);
}

//----------------------------------------------------------------------------------------------

bool Menu::refreshWindow()
{
    int newHeight, newWidth;
    bool sizeErr = false;
    getmaxyx(stdscr,newHeight,newWidth);

    // If terminal dimensions changed
    if ( newHeight != m_HEIGHT || newWidth != m_WIDTH ) {
        delwin(menuWindow);
        cleanUp();
        getmaxyx(stdscr, m_HEIGHT, m_WIDTH);

        // If min dimensions were reached
        if (m_HEIGHT < MIN_HEIGHT) {
            m_HEIGHT = MIN_HEIGHT;
            sizeErr = true;
        }
        else if ( m_WIDTH < MIN_WIDTH ) {
            m_WIDTH = MIN_WIDTH;
            sizeErr = true;
        }

        menuHeight = m_HEIGHT / 2;
        menuWidth = m_WIDTH / 2;
        menuWindow = newwin(menuHeight, menuWidth, m_HEIGHT / 4, m_WIDTH / 4);
        keypad(menuWindow, true);
    }
    box(menuWindow, 0, 0);
    return sizeErr;
}

//----------------------------------------------------------------------------------------------

void Menu::cleanUp()
{
    clear();
    refresh();
}

//----------------------------------------------------------------------------------------------


#include "Menu.hpp"

//----------------------------------------------------------------------------------------------

Menu::Menu()
{}

//----------------------------------------------------------------------------------------------

void Menu::runMenu()
{
    int input;
    size_t currSelect = 0;

    while (running) {
        if ( refreshWindow() )
            displayErr();

        displayName();
        displayHelp();
        printMenuItems( currSelect );
        input = readInput( currSelect);

        if ( input == KEY_ENTER || input == ENTER ) // KEY_ENTER does not work for some reason
            takeAction (currSelect);
    }
    delwin(menuWindow);
    endwin();
    return;
}

//----------------------------------------------------------------------------------------------

int Menu::readInput(size_t& currSelect)
{
    int input = wgetch(menuWindow);
    if ( input == EOT || input == ETX ) { // Check if user pressed ctrl+C or ctrl+D
        running = false;
        return -1;
    }

    switch (input) {
        case KEY_UP:
            if ( currSelect == 0 )
                currSelect = menuItems.size()-1;
            else
                currSelect--;
            break;
        case KEY_DOWN:
            if ( currSelect == menuItems.size()-1)
                currSelect = 0;
            else
                currSelect++;
            break;
        default:
            break;
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
                      menuItems[i].c_str());
        }
        else {
            mvwprintw(menuWindow,
                      (menuHeight / 2 - menuItems.size() / 2 + i),
                      (menuWidth / 2 - menuItems[i].length() / 2),
                      menuItems[i].c_str());
        }
        wattroff(menuWindow, A_STANDOUT);
    }
}

//----------------------------------------------------------------------------------------------

void Menu::displayHelp()
{
    wattron(menuWindow, COLOR_PAIR(6));
    mvwprintw(menuWindow, menuHeight - 2, (menuWidth / 2 - hintMsg.length() / 2), hintMsg.c_str());
    wattroff(menuWindow, COLOR_PAIR(6));
}

//----------------------------------------------------------------------------------------------

void Menu::displayErr()
{
    wattron(menuWindow, COLOR_PAIR(1));
    mvwprintw(menuWindow, 1, (menuWidth / 2 - sizeErrMsg.length() / 2), sizeErrMsg.c_str());
    wattroff(menuWindow, COLOR_PAIR(1));
}

//----------------------------------------------------------------------------------------------

void Menu::displayName()
{
    wattron(menuWindow, COLOR_PAIR(5) | A_UNDERLINE);
    mvwprintw(menuWindow, 2, (menuWidth / 2 - m_Name.length() / 2), m_Name.c_str());
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


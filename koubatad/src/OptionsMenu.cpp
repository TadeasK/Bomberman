#include "OptionsMenu.hpp"

OptionsMenu::OptionsMenu()
    : Menu()
{
    running = true;
    m_Name = "Controls";
    getmaxyx(stdscr,m_WIDTH,m_HEIGHT);
    menuItems = {
            "Back"
    };
}

//----------------------------------------------------------------------------------------------

void OptionsMenu::runMenu()
{
    int input;
    size_t currSelect = 0;

    while (running) {
        if ( refreshWindow() )
            displayErr(sizeErrMsg, "");

        displaySettings();
        displayName();
        displayHelp();
        printMenuItems( currSelect );
        input = readInput( currSelect);

        if ( input == KEY_ENTER || input == ENTER  ) // KEY_ENTER does not work for some reason
            takeAction (currSelect);
    }
    delwin(menuWindow);
}

void OptionsMenu::takeAction(size_t currSelect)
{
    switch (currSelect) {
        case BACK:
            running = false;
            cleanUp();
            break;
    }
}

void OptionsMenu::displaySettings()
{
    for ( size_t i = 0; i < m_SettingKeysP1.size(); i++) { // Prints the settings
        mvwprintw(menuWindow,
                  (menuHeight / 2 - m_SettingKeysP1.size() / 2 + i),
                  ( i == 0 ? (menuWidth / 4 - m_SettingKeysP1[i].length() / 2 ) : ( 2 ) ), // If first item center
                  "%s", m_SettingKeysP1[i].c_str());

        mvwprintw(menuWindow,
                  (menuHeight / 2 - m_SettingKeysP2.size() / 2 + i),
                  ( i == 0 ? (3 * menuWidth / 4 - m_SettingKeysP2[i].length() / 2 ) : ( menuWidth / 2 + 2 ) ),
                  "%s", m_SettingKeysP2[i].c_str());
    }
}
#include "OptionsMenu.hpp"

OptionsMenu::OptionsMenu()
        : Menu()
{
    m_Name = "Controls";
    menuItems = {
            "Back"
    };
}

//----------------------------------------------------------------------------------------------

void OptionsMenu::takeAction(int currSelect)
{
    switch (currSelect) {
        case BACK:
            running = false;
            cleanUp();
            break;
    }
}
//----------------------------------------------------------------------------------------------

void OptionsMenu::displayCustom()
{
    for (size_t i = 0; i < m_SettingKeysP1.size(); i++) { // Prints the settings
        mvwprintw(menuWindow,
                  (menuHeight / 2 - m_SettingKeysP1.size() / 2 + i),
                  (i == 0 ? (menuWidth / 4 - m_SettingKeysP1[i].length() / 2) : (2)), // If first item center
                  "%s", m_SettingKeysP1[i].c_str());

        mvwprintw(menuWindow,
                  (menuHeight / 2 - m_SettingKeysP2.size() / 2 + i),
                  (i == 0 ? (3 * menuWidth / 4 - m_SettingKeysP2[i].length() / 2) : (menuWidth / 2 + 2)),
                  "%s", m_SettingKeysP2[i].c_str());
    }
}
//----------------------------------------------------------------------------------------------

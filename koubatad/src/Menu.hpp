#pragma once

#include <ncurses.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

/**
 * @brief Represents and operates Menu functions, prints Menu windows
 * 
 */
class Menu
{
public:
    /**
     * @brief Constructs a new menu object
     *
     */
    Menu();

    ~Menu();


    /**
     * @brief Operates menus, based on user choice can start the game,
     *  show settings or show help
     * 
     */
    virtual void runMenu();

protected:
    /// Width of window
    int m_WIDTH = 0;
    /// Height of window
    int m_HEIGHT = 0;
    /// Is menu running
    bool running;
    /// Name of Menu
    std::string m_Name;
    /// Items in menu
    std::vector<std::string> menuItems;
    // Height of sub-window
    int menuHeight;
    // Width of sub-window
    int menuWidth;
    /// Pointer to sub-window
    WINDOW *menuWindow;

    // Constants
    const static int MIN_WIDTH = 80; // Minimal width of window to run game
    const static int MIN_HEIGHT = 24; // Minimal height of window to run game
    const static int ENTER = 10; // Alias for ASCII value of ENTER key
    const static int EOT = 4; // Alias for ASCII value of CTRL+D
    const static int ETX = 3; // Alias for ASCII value of CTRL+C
    const std::string hintMsg = "Navigate using ARROW keys and ENTER.";
    const std::string sizeErrMsg = "Terminal reached minimal dimensions!";

    /**
    * @brief Initializes ncurses window, checks if terminal supports all needed functions
    * @throws String error if terminal size is not sufficient or terminal doesn't support color
    *
    */
    void initNcurses();

    /**
     * @brief Set colors to use
     *
     */
    void initColors() const;

    /**
     * @brief Reads, acts upon user input
     * @param currSelect Changes selected menu option based on user input
     * @return integer value of user input
     * 
     */
    virtual int readInput(int &currSelect);

    /**
     *  @brief Print menu items to screen
     *  @param currSelect Which menu option is currently chosen (highlights the option based in this parameter)
     *
     */
    virtual void printMenuItems(size_t currSelect);

    /**
     *  @brief Displays controls help to Menu screen
     */
    virtual void displayHelp();

    /**
     *  @brief Displays error message if an error has occurred
     */
    virtual void displayErr(const std::string &errMsg, const std::string &additionalInfo);

    /**
     *  @brief Displays name of current Menu
     */
    virtual void displayName();

    /**
     * @brief Dynamically changes window size if user changed their terminal size
     * @return True if terminal exceeded minimal dimensions
     *
     */
    virtual bool refreshWindow();

    /**
     * @brief Clears and refreshes screen
     */
    virtual void cleanUp();

    /**
     * @brief Take action based on selected menu option
     * @param currSelect Currently selected option, this option will be executed
     *
     */
    virtual void takeAction(int currSelect) = 0;

    /**
     * @brief Display custom menu options
     */
    virtual void displayCustom() = 0;

    /**
     * @brief Read from score file
     * @param path Path to score file
     * @return Read, formatted score file
     */
    std::map<int, std::pair<std::string, int>> readScoreFile(const std::string &path) const;
};


#include "MainMenu.hpp"
#include <ncurses.h>
#include <iostream>

//----------------------------------------------------------------------------------------------

MainMenu::MainMenu()
{}

//----------------------------------------------------------------------------------------------

MainMenu::~MainMenu()
{
    endwin();
}

//----------------------------------------------------------------------------------------------

bool MainMenu::initNcurses()
{
    initscr(); // Initialize window
    if ( !has_colors() ) {
        std::cerr << "Your terminal doesn't support colors, which is required to run this game."
                  << std::endl; 
        return false;
    }
    start_color(); // Initialize color mode
    initColors(); // Set color pairs

    raw(); // Turn of line buffering
    keypad(stdscr, TRUE); // Activate special keys (arrow, F1...)
    noecho(); // Don't repeat input

    getmaxyx(stdscr, m_HEIGHT, m_WIDTH); // Read window parameters
    
    // Check if terminal has sufficient dimensions
    if ( m_HEIGHT < MIN_HEIGHT || m_WIDTH < MIN_WIDTH ) { 
        std::cerr << "Your terminal is too small. Minumum dimensions of terminal are: "
        << MIN_WIDTH << ":" << MIN_HEIGHT
        << std::endl; 
        return false;
    }

    return true;
}

//----------------------------------------------------------------------------------------------

void MainMenu::menuLoop()
{
    while (true) {

    }

}

//----------------------------------------------------------------------------------------------

void MainMenu::optionsLoop()
{

}

//----------------------------------------------------------------------------------------------

void MainMenu::helpLoop()
{

}

//----------------------------------------------------------------------------------------------

void MainMenu::readInput()
{

}

//----------------------------------------------------------------------------------------------

void MainMenu::initColors()
{
    init_pair(1, COLOR_RED, COLOR_BLACK); // Border color
    init_pair(2, COLOR_RED, COLOR_YELLOW); // Explosion color
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // Bombs, specials color
    init_pair(4, COLOR_GREEN, COLOR_BLACK); // Player color
    init_pair(5, COLOR_BLUE, COLOR_BLACK); // Player2 color
}
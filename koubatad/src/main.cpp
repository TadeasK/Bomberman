#include "MainMenu.hpp"
#include "LevelMenu.hpp"
#include "GameManager.hpp"
#include <iostream>
#include <cstring>
#include <cassert>

void asserts()
{
    // Test corrupted file1 - invalid content
    std::string mapPath = "examples/corruptedMap1";
    std::string scorePath = "assets/scores.txt";
    try {
        GameManager game(true, mapPath, scorePath);
        assert("No exception thrown!" == nullptr);
    }
    catch (std::string &err) {
        std::cout << "Exception \"" << err << "\" caught successfully.\n";
    }

    // Test corrupted file2 - invalid map size
    mapPath = "examples/corruptedMap2";
    try {
        GameManager game(true, mapPath, scorePath);
        assert("No exception thrown!" == nullptr);
    }
    catch (std::string &err) {
        std::cout << "Exception \"" << err << "\" caught successfully.\n";
    }

    // Test corrupted file3 - more than one player entities
    mapPath = "examples/corruptedMap3";
    try {
        GameManager game(true, mapPath, scorePath);
        assert("No exception thrown!" == nullptr);
    }
    catch (std::string &err) {
        std::cout << "Exception \"" << err << "\" caught successfully.\n";
    }

    // Test file readability - no read permissions file
    mapPath = "examples/permissionsMap";
    try {
        GameManager game(true, mapPath, scorePath);
        assert("No exception thrown!" == nullptr);
    }
    catch (std::string &err) {
        std::cout << "Exception \"" << err << "\" caught successfully.\n";
    }

    // Test file readability - nonexistent file
    mapPath = "examples/MapX";
    try {
        GameManager game(true, mapPath, scorePath);
        assert("No exception thrown!" == nullptr);
    }
    catch (std::string &err) {
        std::cout << "Exception \"" << err << "\" caught successfully.\n";
    }

    // TODO testovani - pokrocile
}

int main(int argc, char const *argv[])
{
    bool test = false;
    if (argc > 1 && !strcasecmp(argv[1], "-test")) {
        asserts();
        test = true;
    }

    try {
        MainMenu menu(test);
        menu.runMenu();
    }
    catch (const std::string &err) {
        std::cout << err << std::endl;
        return 1;
    }
    return 0;
}
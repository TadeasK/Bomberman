#include "ExitDoor.hpp"

ExitDoor::ExitDoor( int x, int y,WINDOW* window )
: Special (x,y,window)
{}

// TODO
bool ExitDoor::drawObj() const
{

    return m_Exist;
}

int ExitDoor::giveEffect()
{

}

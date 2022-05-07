#include "Crate.hpp"

Crate::Crate ( int x, int y, bool full )
: Object ( x, y )
{
    m_Filled = full;
}

Crate::~Crate() {    
    if ( m_Filled )
        dropBonus();
}

bool Crate::drawObj() const
{

}

void Crate::dropBonus()
{

}
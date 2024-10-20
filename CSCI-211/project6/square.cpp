// square.cpp
// Raut, Aditya Anil
// araut1
#include "square.h"

Square::Square(int x, int y, int size) : Shape(x, y), size(size) {}


void Square::draw(Grid &grid)
{
    for (int i = 0; i < size; i++)
    {
        grid.set(m_x+i, m_y, '*');
        grid.set(m_x, m_y+i, '*');
        grid.set(m_x+i, m_y+size-1, '*');
        grid.set(m_x+size-1, m_y+size-i-1, '*');
    }
  
}

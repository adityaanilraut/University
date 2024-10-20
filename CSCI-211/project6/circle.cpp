// circle.cpp
// Raut, Aditya Anil
// araut1
#include "circle.h"

Circle::Circle(int x, int y) : Shape(x, y) {}


void Circle::draw(Grid &grid)
{
    for (int i = 0; i < 2; i++)
    {
        grid.set(m_x+1, m_y, 'o');
        grid.set(m_x+2, m_y, 'o');
        grid.set(m_x+1, m_y+3, 'o');
        grid.set(m_x+2, m_y+3, 'o');
        grid.set(m_x, m_y+1, 'o');
        grid.set(m_x, m_y+2, 'o');
        grid.set(m_x+3, m_y+1, 'o');
        grid.set(m_x+3, m_y+2, 'o');
    }
}
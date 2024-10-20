// grip.cpp
// Raut, Aditya Anil
// araut1
#include "grid.h"
#include <iostream>
using namespace std;

Grid::Grid()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            m_grid[i][j] = ' ';
            //m_grid[i][j] = i;
           //m_grid[i][j] = j;

        }
    }
};

void Grid::set(int x, int y,char c){

    if (x >= 0 && y >= 0 && x <COLS  && y < ROWS) {
        m_grid[x][y] = c;

    }
    
    
};

void Grid::print(){
    for (int j = 0; j < ROWS; j++)
    { //int aa;
        for (int i = 0; i < COLS; i++)
        {   
            cout<<m_grid[i][j];
           // aa=j;
        }
        //cout<<aa<<endl;
        cout<<endl;
    }

}
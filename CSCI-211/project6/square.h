// square.h
// Raut, Aditya Anil
// araut1
#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square :public Shape {
  public:
    Square(int x, int y,int size);
    
     void draw(Grid &grid);

  protected:
    //int m_x;
    //int m_y;
    int size;
};

#endif

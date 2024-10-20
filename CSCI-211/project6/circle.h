// ciccle.h
// Raut, Aditya Anil
// araut1
#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

class Circle :public Shape {
  public:
    Circle(int x, int y);
    
     void draw(Grid &grid) ;

  protected:
    //int m_x;
    //int m_y;
    
};

#endif
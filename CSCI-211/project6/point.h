// point.h
// Raut, Aditya Anil
// araut1
#ifndef POINT_H
#define POINT_H

#include "shape.h"

class Point :public Shape {
  public:
    Point(int x, int y,char c);
    //~Point() {}
    virtual void draw(Grid &grid);

  protected:
    //int m_x;
   // int m_y;
    char m_c;
    
};

#endif

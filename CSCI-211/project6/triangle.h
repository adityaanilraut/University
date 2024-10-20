// triangle.h
// Raut, Aditya Anil
// araut1
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "shape.h"

class Triangle :public Shape {
  public:
    Triangle(int x, int y);
    ~Triangle() {}
    void draw(Grid &grid) ;

  protected:
    //int m_x;
   // int m_y;
    //int size;
};

#endif
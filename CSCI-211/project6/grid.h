// grip.h
// Raut, Aditya Anil
// araut1
#ifndef GRID_H
#define GRID_H
static const int COLS = 60;
static const int ROWS = 24;

class Grid
{
    public:
    	Grid();
	    void set(int x, int y, char c);
	    void print();
    private:
    	char m_grid[COLS][ROWS];
};

#endif

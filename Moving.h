#ifndef Moving_h
#define Moving_h

// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <ncurses.h>

using namespace std;

//ΚΛΑΣΗ MOVING
class Moving{
// ATTRIBUTES
protected:
    int y;
	int x;
	int yMax;
	int xMax;
	WINDOW *win;
// ΜΕΘΟΔΟΙ
public:
	Moving(WINDOW *win, int y, int x);
    WINDOW* getWin() const;
	int getY() const;
	int getX() const;
	int getYMax() const;
	int getXMax() const;
	void setWin(WINDOW *Win);
	void setY(int y);
	void setX(int x);
	void setYMax(int yMax);
	void setXMax(int xMax);		
	void move(char direction);
	virtual int getMove() = 0;
};
#endif
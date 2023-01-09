#ifndef Traal_h
#define Traal_h

// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <ncurses.h>
#include "Moving.h"
#include "Potter.h"

using namespace std;

//ΚΛΑΣΗ TRAAL
class Traal: public Moving{
// ATTRIBUTES
private:
	int xPotter;
	int yPotter;
	char symbol;
// ΜΕΘΟΔΟΙ	
public:
	Traal(WINDOW *win, int y, int x, char s);
	char getSymbol() const;
	void setSymbol(char s);
	void checkPotter(int x, int y);
    int getMove();	
    void show();
};
#endif
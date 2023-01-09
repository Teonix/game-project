#ifndef Gnome_h
#define Gnome_h

// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <ncurses.h>
#include "Moving.h"
#include "Potter.h"

using namespace std;

//ΚΛΑΣΗ GNOME
class Gnome: public Moving{
// ATTRIBUTES
private:
	int xPotter;
	int yPotter;
	char symbol;
// ΜΕΘΟΔΟΙ	
public:
	Gnome(WINDOW *win, int y, int x, char s);
	char getSymbol() const;
	void setSymbol(char s);
	void checkPotter(int x, int y);
    int getMove();	
    void show();

};
#endif
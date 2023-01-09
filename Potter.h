#ifndef Potter_h
#define Potter_h

// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <ncurses.h>

using namespace std;

//ΚΛΑΣΗ POTTER
class Potter: public Moving{
// ATTRIBUTES
private:
	char symbol;
// ΜΕΘΟΔΟΙ	
public:
	Potter(WINDOW *win, int y, int x, char s);
	char getSymbol() const;
	void setSymbol(char s);
    int getMove();	
    void reset(int choice);
    void show();	
};
#endif
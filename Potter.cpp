// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <ncurses.h>
#include "Moving.h"
#include "Potter.h"

using namespace std;

// CONSTRUCTOR
Potter::Potter(WINDOW *win, int y, int x, char s):Moving(win,y,x){
    keypad(win, true);
    symbol = s;	
	mvwaddch(win,this->y,this->x,symbol);
	wrefresh(win);
}

// GETTER ΣΥΜΒΟΛΟΥ ΤΟΥ POTTER 'B'
char Potter::getSymbol() const{
	return symbol;
}

// SETTER ΣΥΜΒΟΛΟΥ ΤΟΥ POTTER 'B'
void Potter::setSymbol(char s){
	symbol = s;
}

// Η VIRTUAL ΜΕΘΟΔΟΣ ΚΙΝΗΣΗΣ ΓΙΑ ΤΟΝ POTTER ΜΕ ΤΑ ΒΕΛΑΚΙΑ ΤΟΥ KEYBOARD
int Potter::getMove(){
	int choice = wgetch(win);
	char direction;
    switch(choice)
    {
        case KEY_LEFT:
		    direction = 'l';
            move(direction);			
            break;
        case KEY_RIGHT:
		    direction = 'r';
            move(direction);			
            break;
        case KEY_UP:
            direction = 'u';
            move(direction);			
            break;
        case KEY_DOWN:
            direction = 'd';
            move(direction);			
            break;
        case ' ':
            choice = 5;			
            break;
		default:
		    break;
    }
	return choice;
}

// ΜΕΘΟΔΟΣ ΕΜΦΑΝΙΣΗΣ ΤΗΣ ΝΕΑΣ ΘΕΣΗΣ ΤΟΥ POTTER ΣΤΟΝ ΧΑΡΤΗ
void Potter::show(){
	mvwaddch(win,this->y,this->x,symbol);
	wrefresh(win);
}

// ΜΕΘΟΔΟΣ ΑΝΑΙΡΕΣΗΣ ΤΗΣ ΚΙΝΗΣΗΣ(ΠΡΟΣΚΡΟΥΣΗ ΣΕ ΤΟΙΧΟ)
void Potter::reset(int choice){
    switch(choice)
    {
        case KEY_LEFT:
		    mvwaddch(win,y,x,ACS_CKBOARD);
		    x++;			
            break;
        case KEY_RIGHT:
		    mvwaddch(win,y,x,ACS_CKBOARD);
		    x--;			
            break;
        case KEY_UP:
		    mvwaddch(win,y,x,ACS_CKBOARD);
		    y++;			
            break;
        case KEY_DOWN:
		    mvwaddch(win,y,x,ACS_CKBOARD);
		    y--;			
            break;			
	    default:
		    break;
    }
}
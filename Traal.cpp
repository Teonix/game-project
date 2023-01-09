// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <ncurses.h>
#include "Moving.h"
#include "Traal.h"
#include "Potter.h"

using namespace std;

// CONSTRUCTOR
Traal::Traal(WINDOW *win, int y, int x, char s):Moving(win,y,x){
    symbol = s;
	mvwaddch(win,this->y,this->x,symbol);
	wrefresh(win);
}

// GETTER ΣΥΜΒΟΛΟΥ ΤΟΥ TRAAL 'T'
char Traal::getSymbol() const{
	return symbol;
}

// SETTER ΣΥΜΒΟΛΟΥ ΤΟΥ TRAAL 'T'
void Traal::setSymbol(char s){
	symbol = s;
}

// ΜΕΘΟΔΟΣ ΕΥΡΕΣΗΣ ΤΗΣ ΘΕΣΗΣ ΤΟΥ POTTER
void Traal::checkPotter(int x, int y){
	xPotter = x;
	yPotter = y;
}

// Η VIRTUAL ΜΕΘΟΔΟΣ ΚΙΝΗΣΗΣ ΓΙΑ ΤΟΝ TRAAL
int Traal::getMove(){
	char direction;
	int choice = 0;
	// ΕΠΟΜΕΝΕΣ ΚΙΝΗΣΕΙΣ
	int tmpXplus = this->x+1;
	int tmpXminus = this->x-1;
	int tmpYplus = this->y+1;
	int tmpYminus = this->y-1;

    // ΑΝ ΣΤΗΝ ΕΠΟΜΕΝΗ ΚΙΝΗΣΗ ΒΡΙΣΚΕΤΑΙ Ο POTTER
	if(mvwinch(win,tmpYplus,this->x) == 'B'){
		direction = 'd'; 
        move(direction);
        choice = 1;		
	}
	else if(mvwinch(win,tmpYminus,this->x) == 'B'){
		direction = 'u';
        move(direction);
        choice = 1;			
	}
	else if(mvwinch(win,this->y,tmpXplus) == 'B'){
		direction = 'r';
        move(direction);
        choice = 1;			
	}
	else if(mvwinch(win,this->y,tmpXminus) == 'B'){
		direction = 'l';
        move(direction);
        choice = 1;			
	}
	// ΕΥΡΕΣΗ ΕΠΟΜΕΝΗΣ ΚΙΝΗΣΗΣ ΜΕ ΒΑΣΗ ΤΟ ΠΟΥ ΒΡΙΣΚΕΤΑΙ Ο POTTER ΚΑΙ ΑΝ ΔΕΝ ΥΠΑΡΧΕΙ ΤΟΙΧΟΣ
	// ΔΙΑΦΟΡΟΠΟΙΗΜΕΝΟΣ ΑΠΟ ΤΟΥ GNOME ΩΣ ΠΡΟΣ ΤΗΝ ΕΠΙΛΟΓΗ ΔΕΥΤΕΡΕΥΟΥΣΩΝ ΜΟΝΟΠΑΤΙΩΝ ΛΟΓΩ ΤΟΙΧΟΥ
	// (ΓΙΑ ΝΑ ΓΙΝΕΤΑΙ ΠΕΡΙΚΥΚΛΩΣΗ)
	else{
		if(this->x == xPotter){
			if(this->y < yPotter){
				if(mvwinch(win,tmpYplus,this->x) != ACS_CKBOARD){
					direction = 'd';
					move(direction);			
				}			
				else if(mvwinch(win,this->y,tmpXminus) != ACS_CKBOARD){
					direction = 'l';
					move(direction);
				}
				else if(mvwinch(win,this->y,tmpXplus) != ACS_CKBOARD){
					direction = 'r';
					move(direction);
				}
				else{
					direction = 'u';
					move(direction);					
				}
								
			}
			else if(this->y > yPotter){
				if(mvwinch(win,tmpYminus,this->x) != ACS_CKBOARD){
					direction = 'u';
					move(direction);			
				}
				else if(mvwinch(win,this->y,tmpXminus) != ACS_CKBOARD){
					direction = 'l';
					move(direction);
				}
				else if(mvwinch(win,this->y,tmpXplus) != ACS_CKBOARD){
					direction = 'r';
					move(direction);
				}
				else{
					direction = 'd';
					move(direction);					
				}								
			}
			else if(this->y == yPotter){
				choice =1;				
			}
		}
		else if(this->x < xPotter){
			if(this->y < yPotter){
				if(mvwinch(win,this->y,tmpXplus) != ACS_CKBOARD){
					direction = 'r';
					move(direction);
				}				
				else if(mvwinch(win,tmpYplus,this->x) != ACS_CKBOARD){
					direction = 'd';
					move(direction);			
				}	
				else if(mvwinch(win,this->y,tmpXminus) != ACS_CKBOARD){
					direction = 'l';
					move(direction);					
				}
				else{
					direction = 'u';
					move(direction);
				}								
			}
			else if(this->y > yPotter){
				if(mvwinch(win,this->y,tmpXplus) != ACS_CKBOARD){
					direction = 'r';
					move(direction);
				}
				else if(mvwinch(win,tmpYminus,this->x) != ACS_CKBOARD){
					direction = 'u';
					move(direction);			
				}
				else if(mvwinch(win,this->y,tmpXminus) != ACS_CKBOARD){
					direction = 'l';
					move(direction);					
				}
				else{
					direction = 'd';
					move(direction);
				}								
			}
			else if(this->y == yPotter){
				if(mvwinch(win,this->y,tmpXplus) != ACS_CKBOARD){
					direction = 'r';
					move(direction);			
				}
				else if(mvwinch(win,tmpYplus,this->x) != ACS_CKBOARD){
					direction = 'd';
					move(direction);
				}
				else if(mvwinch(win,tmpYminus,this->x) != ACS_CKBOARD){
					direction = 'u';
					move(direction);
				}
				else{
					direction = 'l';
					move(direction);					
				}				
			}
		}
		else if(this->x > xPotter){
			if(this->y < yPotter){
				if(mvwinch(win,this->y,tmpXminus) != ACS_CKBOARD){
					direction = 'l';
					move(direction);
				}	
				else if(mvwinch(win,tmpYplus,this->x) != ACS_CKBOARD){
					direction = 'd';
					move(direction);			
				}				
				else if(mvwinch(win,this->y,tmpXplus) != ACS_CKBOARD){
					direction = 'r';
					move(direction);					
				}
				else{						
					direction = 'u';
					move(direction);
				}				
			}
			else if(this->y > yPotter){
				if(mvwinch(win,this->y,tmpXminus) != ACS_CKBOARD){
					direction = 'l';
					move(direction);
				}
				else if(mvwinch(win,tmpYminus,this->x) != ACS_CKBOARD){					
					direction = 'u';
					move(direction);			
				}
				else if(mvwinch(win,this->y,tmpXplus) != ACS_CKBOARD){
					direction = 'r';
					move(direction);					
				}
				else{
					direction = 'd';
					move(direction);
				}				
			}
			else if(this->y == yPotter){
				if(mvwinch(win,this->y,tmpXminus) != ACS_CKBOARD){
					direction = 'l';
					move(direction);			
				}
				else if(mvwinch(win,tmpYplus,this->x) != ACS_CKBOARD){
					direction = 'd';
					move(direction);
				}
				else if(mvwinch(win,tmpYminus,this->x) != ACS_CKBOARD){
					direction = 'u';
					move(direction);
				}
				else{
					direction = 'r';
					move(direction);					
				}				
			}
		}
	}
    return choice;	
}

// ΜΕΘΟΔΟΣ ΕΜΦΑΝΙΣΗΣ ΤΗΣ ΝΕΑΣ ΘΕΣΗΣ ΤΟΥ TRAAL ΣΤΟΝ ΧΑΡΤΗ
void Traal::show(){
	mvwaddch(win,this->y,this->x,symbol);
	wrefresh(win);
}
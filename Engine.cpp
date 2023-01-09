// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ncurses.h>
#include "Engine.h"
#include "Moving.h"
#include "Potter.h"
#include "Gnome.h"
#include "Traal.h"
#include "HiScore.h"

using namespace std;

// ΜΕΘΟΔΟΣ ΦΟΡΤΩΣΗΣ ΤΟΥ ΧΑΡΤΗ
void Engine::loadMap(int argc, char **argv){
	fstream file;
	string line;
	file.open(argv[1], ios::in);
	if (!file) {
	    delwin(win);
	    endwin();
		throw 1;
	}
	else {
		while (getline(file, line)){
			map.push_back(line);
		}
	}
	file.close();
}

// ΜΕΘΟΔΟΣ ΦΟΡΤΩΣΗΣ ΤΟΥ ΠΙΝΑΚΑ ΤΩΝ SCORE
void Engine::loadScores(int argc, char **argv){
    fstream in;
	in.open(argv[2], ios::in | ios::binary);
	if (!in) {
	    delwin(win);
	    endwin();
		throw 2;
	}
	else {
		in.read((char *) &Hs, sizeof(Hs));
	}
	in.close();
}

// ΜΕΘΟΔΟΣ ΑΠΟΘΗΚΕΥΣΗΣ ΤΩΝ SCORE
void Engine::saveScores(int argc, char **argv){
    fstream out;
	out.open(argv[2], ios::out | ios::binary);
	if (!out) {
	    delwin(win);
	    endwin();
		throw 2;
	}
	else {
		out.write((char *) &Hs, sizeof(Hs));
	}
	out.close();
}

// CONSTRUCTOR   
Engine::Engine(int argc, char **argv){
	// ΠΕΡΙΠΤΩΣΗ ΛΙΓΟΤΕΡΩΝ ΠΑΡΑΜΕΤΡΩΝ
	if(argc != 3){
		throw 3;
	}
	// ΕΚΚΙΝΗΣΗ ΤΟΥ NCURSES
	initscr();
	noecho();
	cbreak();           
    keypad(stdscr,true);                                              
    curs_set(0);	
	getmaxyx(stdscr, yMax, xMax);

    // ΦΟΡΤΩΣΗ ΤΟΥ ΧΑΡΤΗ
	loadMap(argc,argv);
	// ΦΟΡΤΩΣΗ ΤΩΝ SCORE
	loadScores(argc,argv);
	// ΔΗΜΙΟΥΡΓΙΑ ΠΑΡΑΘΥΡΟΥ
    win = newwin(map.size(),map[0].size()-1,(yMax-map.size())/2,(xMax-map[0].length())/2);
 	refresh();
	// ΓΕΜΙΣΜΑ ΤΟΥ ΠΑΡΑΘΥΡΟΥ ΜΕ ΒΑΣΗ ΤΟΝ ΧΑΡΤΗ
	for(int i = 0; i < map.size(); i++){
		for(int j = 0; j < map[i].size(); j++){
			if(map[i][j] == '*'){
				mvwaddch(win,i,j, ACS_CKBOARD);
			}
			else{
			    mvwaddch(win,i,j,map[i][j]);				
			}
		}
	}
	// ΤΟΠΟΘΕΤΗΣΗ ΠΕΤΡΑΔΙΩΝ
    putDiamonds();	
    wrefresh(win);
	// ΕΚΚΙΝΗΣΗ ΤΟΥ ΠΑΙΧΝΙΔΙΟΥ
	startGame(argc,argv);
}

// ΣΕ ΠΕΡΙΠΤΩΣΗ ΠΡΟΣΚΡΟΥΣΗΣ ΜΕ ΤΟΝ ΤΟΙΧΟ
bool Engine::collision(Moving *player)
{
	int y = player->getY();
	int x = player->getX();
    if(mvwinch(win,y,x) == ACS_CKBOARD){
        return true;
    }
    return false;
}

// ΣΕ ΠΕΡΙΠΤΩΣΗ ΠΡΟΣΚΡΟΥΣΗΣ ΜΕ ΤΑ ΠΕΤΡΑΔΙΑ
bool Engine::collisionDiamonds(Moving *player)
{
	int y = player->getY();
	int x = player->getX();
    if(mvwinch(win,y,x) == ACS_DIAMOND){
        return true;
    }
    return false;
}

// ΣΕ ΠΕΡΙΠΤΩΣΗ ΠΡΟΣΚΡΟΥΣΗΣ ΜΕ ΤΗΝ ΠΕΡΓΑΜΗΝΗ
bool Engine::collisionPergamini(Moving *player)
{
	int y = player->getY();
	int x = player->getX();
    if(mvwinch(win,y,x) == ACS_STERLING){
        return true;
	}
    return false;
}

// ΜΕΘΟΔΟΣ ΤΟΠΟΘΕΤΗΣΗΣ ΤΩΝ 10 ΠΕΤΡΑΔΙΩΝ
void Engine::putDiamonds()
{
	time_t f;
    srand((unsigned) time(&f));
	int counter = 0;
	getmaxyx(win, yMax, xMax);
	while(counter!=10){
		
	    int tmpx=rand()%xMax;
	    int tmpy=rand()%yMax;
		
		if(tmpy >= yMax-2 || tmpy <= 1 || tmpx >= xMax-1 || tmpx == 0){
			continue;
		}

		if(mvwinch(win,tmpy,tmpx) == ACS_CKBOARD || mvwinch(win,tmpy,tmpx) == 'B' || mvwinch(win,tmpy,tmpx) == ACS_DIAMOND){
			continue;
		}
        if(mvwinch(win,tmpy,tmpx) == 'T' || mvwinch(win,tmpy,tmpx) == 'G'){
			continue;
		}
		mvwaddch(win,tmpy,tmpx,ACS_DIAMOND);
		counter++;
	}
}

// ΜΕΘΟΔΟΣ ΤΟΠΟΘΕΤΗΣΗΣ ΤΗΣ ΠΕΡΓΑΜΗΝΗΣ
void Engine::putPergamini(){
	time_t f;
    srand((unsigned) time(&f));
	getmaxyx(win, yMax, xMax);		
	int tmpx;
	int tmpy;
    while(1){
		tmpx=rand()%xMax;
		tmpy=rand()%yMax;
		if(tmpy >= yMax-2 || tmpy <= 1 || tmpx >= xMax-1 || tmpx == 0){
			continue;
		}
        if(mvwinch(win,tmpy,tmpx) == ACS_CKBOARD || mvwinch(win,tmpy,tmpx) == 'B' || mvwinch(win,tmpy,tmpx) == ACS_DIAMOND){
			continue;
		}
        if(mvwinch(win,tmpy,tmpx) == 'T' || mvwinch(win,tmpy,tmpx) == 'G'){
			continue;
		}
		mvwaddch(win,tmpy,tmpx,ACS_STERLING);
		break;
	}
}

// ΕΥΡΕΣΗ ΤΥΧΑΙΟΥ ΣΗΜΕΙΟΥ X ΓΙΑ ΤΗΝ ΤΟΠΟΘΕΤΗΣΗ ΤΩΝ ΤΕΡΑΤΩΝ ΚΑΙ ΤΟΥ POTTER
int Engine::randomX(){
	time_t f;
    srand((unsigned) time(&f));
	getmaxyx(win, yMax, xMax);		
	int tmpx;
	int tmpy;
    while(1){
		tmpx=rand()%xMax;
		tmpy=rand()%yMax;
		if(tmpy >= yMax-2 || tmpy <= 1 || tmpx >= xMax-1 || tmpx == 0){
			continue;
		}
        if(mvwinch(win,tmpy,tmpx) == ACS_CKBOARD || mvwinch(win,tmpy,tmpx) == 'B' || mvwinch(win,tmpy,tmpx) == ACS_DIAMOND){
			continue;
		}
        if(mvwinch(win,tmpy,tmpx) == 'T' || mvwinch(win,tmpy,tmpx) == 'G'){
			continue;
		}
		break;
	}
	return tmpx;
}

// ΕΥΡΕΣΗ ΤΥΧΑΙΟΥ ΣΗΜΕΙΟΥ Y ΓΙΑ ΤΗΝ ΤΟΠΟΘΕΤΗΣΗ ΤΩΝ ΤΕΡΑΤΩΝ ΚΑΙ ΤΟΥ POTTER
int Engine::randomY(){
	time_t f;
    srand((unsigned) time(&f));
	getmaxyx(win, yMax, xMax);		
	int tmpx;
	int tmpy;
    while(1){
		tmpx=rand()%xMax;
		tmpy=rand()%yMax;
		if(tmpy >= yMax-2 || tmpy <= 1 || tmpx >= xMax-1 || tmpx == 0){
			continue;
		}
        if(mvwinch(win,tmpy,tmpx) == ACS_CKBOARD || mvwinch(win,tmpy,tmpx) == 'B' || mvwinch(win,tmpy,tmpx) == ACS_DIAMOND){
			continue;
		}
        if(mvwinch(win,tmpy,tmpx) == 'T' || mvwinch(win,tmpy,tmpx) == 'G'){
			continue;
		}
		break;
	}
	return tmpy;
}

// ΜΕΘΟΔΟΣ ΕΚΚΙΝΗΣΗ ΠΑΙΧΝΙΔΙΟΥ
void Engine::startGame(int argc, char **argv)
{
	int counter = 0;
	int choice;	
	int choiceG;
	int choiceT;
	bool colDiamT = false;
	bool colDiamG = false;
	bool colPergT = false;
	bool colPergG = false;
	getmaxyx(win, yMax, xMax);
	string congrats = "You won! Congrats!";
	string exit = "Press 'c' to continue...";
	int score = 0;

    // ΤΟΠΟΘΕΤΗΣΗ ΤΟΥ POTTER
	int tmpxP = randomX();
	int tmpyP = randomY();
	Potter p(win,tmpyP,tmpxP,'B');
	
	// ΤΟΠΟΘΕΤΗΣΗ ΤΟΥ TRAAL
	int tmpxT = randomX();
	int tmpyT = randomY();
	Traal t(win,tmpyT,tmpxT,'T');
	
	// ΤΟΠΟΘΕΤΗΣΗ ΤΟΥ GNOME
	int tmpxG = randomX();
	int tmpyG = randomY();
	Gnome g(win,tmpyG,tmpxG,'G');
	
	// ΕΝΑΡΞΗ ΤΩΝ ΓΥΡΩΝ ΤΟΥ ΠΑΙΧΝΙΔΙΟΥ
    while((choice = p.getMove())!= 27){
		// ΑΝ Η ΚΙΝΗΣΗ ΤΟΥ POTTER ΗΤΑΝ ΤΟ SPACE
		if(choice == 5){
			// ΚΙΝΗΣΗ ΤΟΥ TRAAL
	        t.checkPotter(p.getX(),p.getY());
	        choiceT = t.getMove();
			// ΕΛΕΓΧΟΣ ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΤΟΝ POTTER
			if(choiceT == 1){
				// ΛΗΞΗ ΤΟΥ ΠΑΙΧΝΙΔΙΟΥ
				getmaxyx(win, yMax, xMax);
				string lose = "You lose! Game Over.";
				string exit = "Press 'c' to continue...";
				char msg1[]="Enter your name: ";
				char inputName[11];			
				werase(win);
				start_color();
				init_pair(2,COLOR_GREEN,COLOR_WHITE);
				attron(COLOR_PAIR(2));
				mvwprintw(win,(yMax/2)-2,(xMax-lose.size())/2,lose.c_str());
				mvwprintw(win,yMax/2,(xMax-lose.size())/2,"Your score: %d",score);
				mvwprintw(win,(yMax/2)+2,(xMax-lose.size())/2,exit.c_str());
				attroff(COLOR_PAIR(2));
				wbkgd(win, COLOR_PAIR(2)); 
				wrefresh(win);
				while(wgetch(win)!='c'){
					continue;
				}	
				echo();		
				do{	
					werase(win);
					mvwprintw(win,yMax/2,(xMax-strlen(msg1))/2,"%s",msg1);				
					wgetnstr(win,inputName,10);				
				}while(strlen(inputName)==0);
				Hs << score << inputName;
				saveScores(argc,argv);
				break;
			}
			// ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ, ΤΟΤΕ ΜΕ ΒΑΣΗ ΤΙΣ "TEMP" ΣΥΝΤΕΤΑΓΜΕΝΕΣ ΞΑΝΑΤΟΠΟΘΕΤΕΙΤΑΙ ΤΟ ΠΕΤΡΑΔΙ
			if(colDiamT){
				colDiamT = false;
				mvwaddch(win,tmpyT,tmpxT,ACS_DIAMOND);
			}
			// ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ, ΤΟΤΕ ΜΕ ΒΑΣΗ ΤΙΣ  "TEMP" ΣΥΝΤΕΤΑΓΜΕΝΕΣ ΞΑΝΑΤΟΠΟΘΕΤΕΙΤΑΙ Η ΠΕΡΓΑΜΗΝΗ
			if(colPergT){
				colPergT = false;
				mvwaddch(win,tmpyT,tmpxT,ACS_STERLING);
			}
			// ΕΛΕΓΧΟΣ ΑΝ ΥΠΗΡΞΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΠΕΤΡΑΔΙ ΑΠΟ ΤΟΝ TRAAL
			if(collisionDiamonds(&t)){
				colDiamT = true;
				tmpxT = t.getX();
				tmpyT = t.getY();
			}
			// ΕΛΕΓΧΟΣ ΑΝ ΥΠΗΡΞΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΤΗ ΠΕΡΓΑΜΗΝΗ ΑΠΟ ΤΟΝ TRAAL
			if(collisionPergamini(&t)){
				colPergT = true;
				tmpxT = t.getX();
				tmpyT = t.getY();
			}
			// ΕΜΦΑΝΙΣΗ ΤΟΥ TRAAL ΣΤΗ ΝΕΑ ΘΕΣΗ
			t.show();
			// ΚΙΝΗΣΗ ΤΟΥ TRAAL
			g.checkPotter(p.getX(),p.getY());
			choiceG = g.getMove();
			// ΕΛΕΓΧΟΣ ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΤΟΝ POTTER
			if(choiceG == 1){
				// ΛΗΞΗ ΤΟΥ ΠΑΙΧΝΙΔΙΟΥ
				getmaxyx(win, yMax, xMax);
				string lose = "You lose! Game Over.";
				string exit = "Press 'c' to continue...";
				char msg1[]="Enter your name: ";
				char inputName[11];			
				werase(win);
				start_color();
				init_pair(2,COLOR_GREEN,COLOR_WHITE);
				attron(COLOR_PAIR(2));
				mvwprintw(win,(yMax/2)-2,(xMax-lose.size())/2,lose.c_str());
				mvwprintw(win,yMax/2,(xMax-lose.size())/2,"Your score: %d",score);
				mvwprintw(win,(yMax/2)+2,(xMax-lose.size())/2,exit.c_str());
				attroff(COLOR_PAIR(2));
				wbkgd(win, COLOR_PAIR(2)); 
				wrefresh(win);
				while(wgetch(win)!='c'){
					continue;
				}	
				echo();		
				do{	
					werase(win);
					mvwprintw(win,yMax/2,(xMax-strlen(msg1))/2,"%s",msg1);				
					wgetnstr(win,inputName,10);				
				}while(strlen(inputName)==0);
				Hs << score << inputName;
				saveScores(argc,argv);
				break;
			}
			// ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ, ΤΟΤΕ ΜΕ ΒΑΣΗ ΤΙΣ "TEMP" ΣΥΝΤΕΤΑΓΜΕΝΕΣ ΞΑΝΑΤΟΠΟΘΕΤΕΙΤΑΙ ΤΟ ΠΕΤΡΑΔΙ
			if(colDiamG){
				colDiamG = false;
				mvwaddch(win,tmpyG,tmpxG,ACS_DIAMOND);
			}
			// ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ, ΤΟΤΕ ΜΕ ΒΑΣΗ ΤΙΣ "TEMP" ΣΥΝΤΕΤΑΓΜΕΝΕΣ ΞΑΝΑΤΟΠΟΘΕΤΕΙΤΑΙ Η ΠΕΡΓΑΜΗΝΗ
			if(colPergG){
				colPergG = false;
				mvwaddch(win,tmpyG,tmpxG,ACS_STERLING);
			}
			// ΕΛΕΓΧΟΣ ΑΝ ΥΠΗΡΞΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΠΕΤΡΑΔΙ ΑΠΟ ΤΟΝ GNOME
			if(collisionDiamonds(&g)){
				colDiamG = true;
				tmpxG = g.getX();
				tmpyG = g.getY();
			}
			// ΕΛΕΓΧΟΣ ΑΝ ΥΠΗΡΞΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΤΗ ΠΕΡΓΑΜΗΝΗ ΑΠΟ ΤΟΝ GNOME
			if(collisionPergamini(&g)){
				colPergG = true;
				tmpxG = g.getX();
				tmpyG = g.getY();
			}
			// ΕΜΦΑΝΙΣΗ ΤΟΥ GNOME ΣΤΗ ΝΕΑ ΘΕΣΗ
			g.show();
			continue;
		}
		// ΕΛΕΓΧΟΣ ΑΝ Ο POTTER ΕΠΕΣΕ ΠΑΝΩ ΣΤΗ ΠΕΡΓΑΜΗΝΗ
		if(collisionPergamini(&p)){
			// ΛΗΞΗ ΤΟΥ ΠΑΙΧΝΙΔΙΟΥ
			score+=100;
			char msg1[]="Enter your name: ";
            char inputName[11];			
			werase(win);
			start_color();
			init_pair(1,COLOR_RED,COLOR_WHITE);
			attron(COLOR_PAIR(1));
			mvwprintw(win,(yMax/2)-2,(xMax-congrats.size())/2,congrats.c_str());
			mvwprintw(win,yMax/2,(xMax-congrats.size())/2,"Your score: %d",score);
			mvwprintw(win,(yMax/2)+2,(xMax-congrats.size())/2,exit.c_str());
			attroff(COLOR_PAIR(1));
			wbkgd(win, COLOR_PAIR(1)); 
			wrefresh(win);
			while(wgetch(win)!='c'){
				continue;
			}	
            echo();		
			do{	
			    werase(win);
			    mvwprintw(win,yMax/2,(xMax-strlen(msg1))/2,"%s",msg1);				
                wgetnstr(win,inputName,10);				
			}while(strlen(inputName)==0);
			Hs << score << inputName;
			saveScores(argc,argv);			
            break;			
		}
		// ΕΛΕΓΧΟΣ ΑΝ Ο POTTER ΕΠΕΣΕ ΠΑΝΩ ΣΕ ΠΕΤΡΑΔΙ
		if(collisionDiamonds(&p)){
		    counter++;
            score+=10; 			
		}
        // ΑΝ Ο POTTER ΔΕΝ ΕΠΕΣΕ ΠΑΝΩ ΣΕ ΤΟΙΧΟ		
        if(!collision(&p)){
			// ΕΜΦΑΝΙΣΗ ΝΕΑΣ ΘΕΣΗΣ ΤΟΥ POTTER
		    p.show();
			// ΑΝ Η ΚΙΝΗΣΗ ΤΟΥ ΠΑΙΚΤΗ ΗΤΑΝ ΤΑ ΒΕΛΑΚΙΑ ΤΟΤΕ ΤΑ ΤΕΡΑΤΑ ΜΠΟΡΟΥΝ ΝΑ ΚΙΝΗΘΟΥΝ
			if(choice == KEY_LEFT || choice == KEY_RIGHT || choice == KEY_UP || choice == KEY_DOWN){
				// ΚΙΝΗΣΗ ΤΟΥ TRAAL
				t.checkPotter(p.getX(),p.getY());
				choiceT = t.getMove();
				// ΕΛΕΓΧΟΣ ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΤΟΝ POTTER
				if(choiceT == 1){
					// ΛΗΞΗ ΤΟΥ ΠΑΙΧΝΙΔΙΟΥ
					getmaxyx(win, yMax, xMax);
					string lose = "You lose! Game Over.";
					string exit = "Press 'c' to continue...";
					char msg1[]="Enter your name: ";
					char inputName[11];			
					werase(win);
					start_color();
					init_pair(2,COLOR_GREEN,COLOR_WHITE);
					attron(COLOR_PAIR(2));
					mvwprintw(win,(yMax/2)-2,(xMax-lose.size())/2,lose.c_str());
					mvwprintw(win,yMax/2,(xMax-lose.size())/2,"Your score: %d",score);
					mvwprintw(win,(yMax/2)+2,(xMax-lose.size())/2,exit.c_str());
					attroff(COLOR_PAIR(2));
					wbkgd(win, COLOR_PAIR(2)); 
					wrefresh(win);
					while(wgetch(win)!='c'){
						continue;
					}	
					echo();		
					do{	
						werase(win);
						mvwprintw(win,yMax/2,(xMax-strlen(msg1))/2,"%s",msg1);				
						wgetnstr(win,inputName,10);				
					}while(strlen(inputName)==0);
					Hs << score << inputName;
					saveScores(argc,argv);
					break;
				}
				// ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ, ΤΟΤΕ ΜΕ ΒΑΣΗ ΤΙΣ "TEMP" ΣΥΝΤΕΤΑΓΜΕΝΕΣ ΞΑΝΑΤΟΠΟΘΕΤΕΙΤΑΙ ΤΟ ΠΕΤΡΑΔΙ
				if(colDiamT){
					colDiamT = false;
					mvwaddch(win,tmpyT,tmpxT,ACS_DIAMOND);
				}
				// ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ, ΤΟΤΕ ΜΕ ΒΑΣΗ ΤΙΣ "TEMP" ΣΥΝΤΕΤΑΓΜΕΝΕΣ ΞΑΝΑΤΟΠΟΘΕΤΕΙΤΑΙ Η ΠΕΡΓΑΜΗΝΗ
				if(colPergT){
					colPergT = false;
					mvwaddch(win,tmpyT,tmpxT,ACS_STERLING);
				}
				// ΕΛΕΓΧΟΣ ΑΝ ΥΠΗΡΞΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΠΕΤΡΑΔΙ ΑΠΟ ΤΟΝ TRAAL
				if(collisionDiamonds(&t)){
					colDiamT = true;
					tmpxT = t.getX();
					tmpyT = t.getY();
				}
				// ΕΛΕΓΧΟΣ ΑΝ ΥΠΗΡΞΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΤΗ ΠΕΡΓΑΜΗΝΗ ΑΠΟ ΤΟΝ TRAAL
				if(collisionPergamini(&t)){
					colPergT = true;
					tmpxT = t.getX();
					tmpyT = t.getY();
				}
				// ΕΜΦΑΝΙΣΗ ΤΟΥ TRAAL ΣΤΗ ΝΕΑ ΘΕΣΗ
				t.show();
				// ΚΙΝΗΣΗ ΤΟΥ GNOME
				g.checkPotter(p.getX(),p.getY());
				choiceG = g.getMove();
				// ΕΛΕΓΧΟΣ ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΤΟΝ POTTER
				if(choiceG == 1){
					// ΛΗΞΗ ΤΟΥ ΠΑΙΧΝΙΔΙΟΥ
					getmaxyx(win, yMax, xMax);
					string lose = "You lose! Game Over.";
					string exit = "Press 'c' to continue...";
					char msg1[]="Enter your name: ";
					char inputName[11];			
					werase(win);
					start_color();
					init_pair(2,COLOR_GREEN,COLOR_WHITE);
					attron(COLOR_PAIR(2));
					mvwprintw(win,(yMax/2)-2,(xMax-lose.size())/2,lose.c_str());
					mvwprintw(win,yMax/2,(xMax-lose.size())/2,"Your score: %d",score);
					mvwprintw(win,(yMax/2)+2,(xMax-lose.size())/2,exit.c_str());
					attroff(COLOR_PAIR(2));
					wbkgd(win, COLOR_PAIR(2)); 
					wrefresh(win);
					while(wgetch(win)!='c'){
						continue;
					}	
					echo();		
					do{	
						werase(win);
						mvwprintw(win,yMax/2,(xMax-strlen(msg1))/2,"%s",msg1);				
						wgetnstr(win,inputName,10);				
					}while(strlen(inputName)==0);
					Hs << score << inputName;
					saveScores(argc,argv);
					break;
				}
				// ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ, ΤΟΤΕ ΜΕ ΒΑΣΗ ΤΙΣ "TEMP" ΣΥΝΤΕΤΑΓΜΕΝΕΣ ΞΑΝΑΤΟΠΟΘΕΤΕΙΤΑΙ ΤΟ ΠΕΤΡΑΔΙ
				if(colDiamG){
					colDiamG = false;
					mvwaddch(win,tmpyG,tmpxG,ACS_DIAMOND);
				}
				// ΑΝ ΕΓΙΝΕ ΠΡΟΣΚΡΟΥΣΗ, ΤΟΤΕ ΜΕ ΒΑΣΗ ΤΙΣ "TEMP" ΣΥΝΤΕΤΑΓΜΕΝΕΣ ΞΑΝΑΤΟΠΟΘΕΤΕΙΤΑΙ Η ΠΕΡΓΑΜΗΝΗ
				if(colPergG){
					colPergG = false;
					mvwaddch(win,tmpyG,tmpxG,ACS_STERLING);
				}
				// ΕΛΕΓΧΟΣ ΑΝ ΥΠΗΡΞΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΠΕΤΡΑΔΙ ΑΠΟ ΤΟΝ GNOME
				if(collisionDiamonds(&g)){
					colDiamG = true;
					tmpxG = g.getX();
					tmpyG = g.getY();
				}
				// ΕΛΕΓΧΟΣ ΑΝ ΥΠΗΡΞΕ ΠΡΟΣΚΡΟΥΣΗ ΜΕ ΤΗ ΠΕΡΓΑΜΗΝΗ ΑΠΟ ΤΟΝ GNOME
				if(collisionPergamini(&g)){
					colPergG = true;
					tmpxG = g.getX();
					tmpyG = g.getY();
				}
				// ΕΜΦΑΝΙΣΗ ΤΟΥ GNOME ΣΤΗ ΝΕΑ ΘΕΣΗ
				g.show();				
			}
			// ΕΛΕΓΧΟΣ ΑΝ ΜΑΖΕΥΤΗΚΑΝ ΟΛΑ ΤΑ ΠΕΤΡΑΔΙΑ
			if(counter == 10){
				// ΤΟΠΟΘΕΤΗΣΗ ΠΕΡΓΑΜΗΝΗΣ
			    putPergamini();
                counter = 0;				
            } 
            wrefresh(win);			
		}else{
			// ΣΕ ΠΕΡΙΠΤΩΣΗ ΠΟΥ Η ΚΙΝΗΣΗ ΗΤΑΝ ΠΑΡΑΝΟΜΗ ΓΙΝΕΤΑΙ ΕΠΑΝΑΦΟΡΑ ΤΗΣ ΠΡΟΗΓΟΥΜΕΝΗΣ ΘΕΣΗΣ
			p.reset(choice);
			// ΕΜΦΑΝΙΣΗ ΤΗΣ ΠΑΛΙΑΣ ΘΕΣΗΣ
			p.show();	
		}
    }
    // ΚΑΤΑΣΤΡΟΦΗ ΠΑΡΑΘΥΡΟΥ	
	delwin(win);
	// ΚΛΕΙΣΙΜΟ ΤΗΣ NCURSES
	endwin();
}
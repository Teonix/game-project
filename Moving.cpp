// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <ncurses.h>
#include "Moving.h"

using namespace std;

// CONSTRUCTOR
Moving::Moving(WINDOW *win, int y, int x){
	this->win = win;
	this->y = y;
	this->x = x;
	getmaxyx(win,yMax,xMax);
}

// ΜΕΘΟΔΟΣ ΚΙΝΗΣΗΣ ΑΝΤΙΚΕΙΜΕΝΩΝ ΣΤΟΝ ΧΑΡΤΗ
void Moving::move(char direction){
    switch(direction)
    {
        case 'l':
		    mvwaddch(win,y,x,' ');
		    x--;			
            break;
        case 'r':
		    mvwaddch(win,y,x,' ');
		    x++;	
            break;
        case 'u':
		    mvwaddch(win,y,x,' ');
            y--;		   
            break;
        case 'd':
		    mvwaddch(win,y,x,' ');
            y++;		   
            break;			
	    default:
		    break;
    }
}

// GETTER WIN(ΠΑΡΑΘΥΡΟ)
WINDOW* Moving::getWin() const{
	return win;
}

// GETTER Y(ΘΕΣΗΣ ΑΝΤΙΚΕΙΜΕΝΟΥ)
int Moving::getY() const{
	return y;
}

// GETTER X(ΘΕΣΗΣ ΑΝΤΙΚΕΙΜΕΝΟΥ)
int Moving::getX() const{
	return x;
}

// GETTER YMAX(ΠΑΡΑΘΥΡΟΥ)
int Moving::getYMax() const{
	return yMax;
}

// GETTER XMAX(ΠΑΡΑΘΥΡΟΥ)
int Moving::getXMax() const{
	return xMax;
}

// SETTER WIN(ΠΑΡΑΘΥΡΟ)
void Moving::setWin(WINDOW *Win){
	this->win = win;
}

// SETTER Y(ΘΕΣΗΣ ΑΝΤΙΚΕΙΜΕΝΟΥ)
void Moving::setY(int y){
	this->y = y;
}

// SETTER X(ΘΕΣΗΣ ΑΝΤΙΚΕΙΜΕΝΟΥ)
void Moving::setX(int x){
	this->x = x;
}

// SETTER YMAX(ΠΑΡΑΘΥΡΟΥ)	
void Moving::setYMax(int yMax){
	this->yMax = yMax;
}

// SETTER XMAX(ΠΑΡΑΘΥΡΟΥ)
void Moving::setXMax(int xMax){
	this->xMax = xMax;
}
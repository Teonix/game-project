#ifndef Engine_h
#define Engine_h

// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <stdio.h>
#include <vector>
#include <ncurses.h>
#include "Moving.h"
#include "Potter.h"
#include "Gnome.h"
#include "Traal.h"
#include "HiScore.h"

using namespace std;

//ΚΛΑΣΗ ENGINE
class Engine{
// ATTRIBUTES
private:
	int xMax;
	int yMax;
	WINDOW *win;
	vector<string> map;
    HiScore Hs;
// ΜΕΘΟΔΟΙ
public:
	Engine(int argc, char **argv);	
	void loadMap(int argc, char **argv);
	void loadScores(int argc, char **argv);
    void saveScores(int argc, char **argv);	
	bool collision(Moving *player);
    bool collisionDiamonds(Moving *player);
    bool collisionPergamini(Moving *player);
    void startGame(int argc, char **argv);
	void putDiamonds();
	void putPergamini();
    int randomY();
    int randomX();
};
#endif
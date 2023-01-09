#ifndef HiScore_h
#define HiScore_h

// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>

using namespace std;

// ΚΛΑΣΗ ΜΕ ΤΑ HIGH SCORES
class HiScore{
// ATTRIBUTES
private:
	char name[5][11];
    int score[5];
// ΜΕΘΟΔΟΙ	
public:
	void setName(char name[][11]);
	void setScore(int score[]);
    void operator<< (char Name[]);
	HiScore& operator<< (int Score);
};
#endif
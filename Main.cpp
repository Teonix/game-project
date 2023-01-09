// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include <ncurses.h>
#include "Engine.h"

using namespace std;

// ΤΟ MAIN ΠΡΟΓΡΑΜΜΑ
int main (int argc, char **argv)
{
	// ΕΛΕΓΧΟΣ ΓΙΑ ΣΦΑΛΜΑΤΑ ΠΟΥ ΑΦΟΡΟΥΝ ΤΑ ΑΡΧΕΙΑ
	try{
	// ΔΗΜΙΟΥΡΓΙΑ ΑΝΤΙΚΕΙΜΕΝΟΥ ΤΗΣ ΚΛΑΣΗΣ ENGINE
	Engine e(argc,argv);
	}catch(int x){
		if(x == 1){
		    cout << "Error..This map file doesn't exist." << endl;
		}
		else if(x == 2){
			cout << "Error..This score file doesn't exist." << endl;
		}
		else if(x == 3){
			cout << "Error..You must give map and score files." << endl;
		}
	}catch(...){
		cout << "Error." << endl;
	}
	
	return 0;
}
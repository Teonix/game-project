// ΕΙΣΟΔΟΣ ΒΙΒΛΙΟΘΗΚΩΝ
#include <iostream>
#include "HiScore.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

// ΥΠΕΡΦΟΡΤΩΣΗ ΤΟΥ ΤΕΛΕΣΤΗ '<<' ΓΙΑ ΤΗΝ ΚΑΤΑΧΩΡΙΣΗ ΤΟΥ SCORE ΣΤΟΝ ΠΙΝΑΚΑ
// ΤΑΥΤΟΧΡΟΝΑ ΓΙΝΕΤΑΙ ΕΛΕΓΧΟΣ ΑΝ ΤΟ SCORE ΜΠΟΡΕΙ ΝΑ ΜΠΕΙ ΣΤΟΝ ΠΙΝΑΚΑ
// ΣΕ ΠΕΡΙΠΤΩΣΗ ΠΟΥ ΠΡΕΠΕΙ ΝΑ ΜΠΕΙ, ΓΙΝΕΤΑΙ ΚΑΙ ΤΑΞΙΝΟΜΗΣΗ ΤΟΥ ΠΙΝΑΚΑ
// ΣΤΟ ΣΗΜΕΙΟ ΠΟΥ ΜΠΑΙΝΕΙ ΤΟ SCORE ΤΟ ΟΝΟΜΑ ΤΟΥ ΠΑΙΚΤΗ ΟΝΟΜΑΖΕΤΑΙ "Change" 
HiScore& HiScore::operator<< (int Score){
	int tmpScore[5];
	char tmpName[5][11];
	memcpy(tmpScore,score,sizeof(int)*5);
	memcpy(tmpName,name,sizeof(char)*55);
    for(int i=0; i<5; i++){
		if(score[i] < Score){
			score[i] = Score;
			strcpy(name[i],"Change");
			for(int j=i+1; j<5; j++){
				score[j] = tmpScore[j-1];
				strcpy(name[j],tmpName[j-1]);
			}
		    break;
		}
	}
    return *this;	
}

// ΥΠΕΡΦΟΡΤΩΣΗ ΤΟΥ ΤΕΛΕΣΤΗ '<<' 
// ΓΙΑ ΤΗΝ ΚΑΤΑΧΩΡΙΣΗ ΤΟΥ ΟΝΟΜΑΤΟΣ ΤΟΥ ΠΑΙΚΤΗ ΣΤΗ ΘΕΣΗ ΜΕ ΤΟ ΟΝΟΜΑ "Change"
void HiScore::operator<< (char Name[]){
    for(int i=0; i<5; i++){
		if(strcmp(name[i],"Change") == 0){
			strcpy(name[i],Name);
			break;
		}
	}
}

// SETTER ΤΩΝ ΟΝΟΜΑΤΩΝ ΤΩΝ ΠΑΙΚΤΩΝ
void HiScore::setName(char Name[][11]){
	for(int i=0; i<5; i++){
		strcpy(name[i],Name[i]);
	}
}

// SETTER ΤΩΝ SCORE ΤΩΝ ΠΑΙΚΤΩΝ
void HiScore::setScore(int score[]){
	for(int i=0; i<5; i++){
		this->score[i] = score[i];
	}
}
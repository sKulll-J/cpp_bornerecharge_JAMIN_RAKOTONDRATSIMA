#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H
#include <lcarte.h>



class LecteurCarte
{	
  	public :
  	int carte_id ;
	
	LecteurCarte();
	
	void lire_carte();
	int get_id();
};

#endif // LECTEURCARTE_H

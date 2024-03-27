#include"bouton.h"

#include<donnees_borne.h>
#include<memoire_borne.h>

entrees* io ;
int shmid ;

void Bouton :: Bouton()
{
	io=acces_memoire(&shmid);
}


int Bouton :: charge()
{
	int state = io->bouton_charge ;	
	return state ;
	
}

int Bouton :: stop()
{
	int state = io->bouton_stop ;	
	return state ;
}
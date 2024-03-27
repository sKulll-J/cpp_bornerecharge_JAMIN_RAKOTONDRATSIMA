#include<stdio.h>

#include "bouton.h"

#include<donnees_borne.h>
#include<memoire_borne.h>

entrees* io ;
int shmid ;

void init_bouton()
{
	io=acces_memoire(&shmid);
}


int bouton_charge()
{
	int state = io->bouton_charge ;	
	return state ;
	
}

int bouton_stop()
{
	int state = io->bouton_stop ;	
	return state ;
}

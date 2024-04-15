#include "prise.h"

#include<donnees_borne.h>
#include<memoire_borne.h>

entrees* io ;
//int shmid ;

Prise :: Prise()
{
    io=acces_memoire(&shmid);
}

void Prise :: verouiller_trappe()
{
	io->led_trappe = OFF ;
}

void Prise :: deverouiller_trappe()
{
	io->led_trappe = VERT;
}

void Prise :: set_prise(int etat)
{
	switch(etat)
	{	case 0: 
			io->led_prise = ROUGE ;
			break ;
		case 1:
			io->led_prise = VERT;
			break ;
		default:
			io->led_prise = OFF; 
			break;	
	}
}

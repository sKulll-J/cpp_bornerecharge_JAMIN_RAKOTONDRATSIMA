#include "prise.h"
#include<stdio.h>
#include<donnees_borne.h>
#include<memoire_borne.h>

entrees* io ;
int shmid ;

void init_prise()
{
	io=acces_memoire(&shmid);
}
void prise_verouiller_trappe()
{
	io->led_trappe = OFF ;
}

void prise_deverouiller_trappe()
{
	io->led_trappe = VERT;
}

void prise_set_prise(int etat)
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

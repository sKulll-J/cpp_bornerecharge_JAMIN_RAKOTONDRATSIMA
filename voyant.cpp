#include<stdio.h>
#include <unistd.h>

#include "voyant.h"
#include "timer.h"

#include<donnees_borne.h>
#include<memoire_borne.h>

entrees * io ;

int shmid ;
int timer_start   ;
int timer_sec = 0;

voyant :: voyant()
{
    io = access_memoire(&shmid) ;
}

void voyant :: blink_charge()
{
	io->led_charge = OFF ;
	usleep( 500000 ); // attente 0.5 s
	io->led_charge = VERT ;
	usleep( 500000 ); // attente 0.5 s
}

void voyant :: set_dispo(int etat)
{	

	switch(etat)
	{	case 0: 
			io->led_dispo = OFF ;
			break ;
		case 1:
			io->led_dispo = VERT;
			break ;
		default:
			io->led_dispo = OFF; 
			break;	
	}
		
}

void voyant :: set_default(int etat)
{	

	switch(etat)
	{	case 0: 
			io->led_defaut = OFF ;
			break ;
		case 1:
			io->led_defaut = VERT;
			break ;
		case 2:
			io->led_defaut = ROUGE;
			break ;
		default:
			io->led_defaut = OFF; 
			break;	
	}
		
}

void voyant :: set_charge(int etat)
{	

	switch(etat)
	{	case 0: 
			io->led_charge = OFF ;
			break ;
		case 1:
			io->led_charge = VERT;
			break ;
		case 2:
			io->led_charge = ROUGE;
			break ;
		default:
			io->led_charge = OFF; 
			break;	
	}
		
}
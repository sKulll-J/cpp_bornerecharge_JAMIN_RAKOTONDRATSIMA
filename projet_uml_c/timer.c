#include<stdio.h>
#include <unistd.h>
#include<time.h>

#include "timer.h"

#include<donnees_borne.h>
#include<memoire_borne.h>

entrees* io ;

int shmid ;
int depart_timer ;

time_t now ; // temps actuel
time_t start_time ;
//====================================================

void init_timer()
{
	io=acces_memoire(&shmid);
	now = time(NULL);
	depart_timer = (int)now ;
}

void timer_raz(int* strt)
{
	*strt = (int) time(NULL);
}

int timer_elapsed(int* delta, int* strt)
{
	now=time(NULL);
	*delta = (int) (now )- *strt;
	//printf("delt_time %d\n", *delta);
	return *delta;
}

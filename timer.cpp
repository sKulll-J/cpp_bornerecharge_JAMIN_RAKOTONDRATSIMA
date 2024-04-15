#include"timer.h"

#include<donnees_borne.h>
#include<memoire_borne.h>

#include <unistd.h>
#include <time.h>


//entrees* io ;
//int shmid ;

int depart_timer ;

time_t now ; // temps actuel
time_t start_time ;

// ==========================================

Timer :: Timer()
{
    io=acces_memoire(&shmid);
	now = time(NULL);
	depart_timer = (int)now ;
}

void Timer :: raz(int* strt)
{
	*strt = (int) time(NULL);
}

int Timer :: elapsed(int* delta, int* strt)
{
	now=time(NULL);
	*delta = (int) (now )- *strt;

	return *delta;
}

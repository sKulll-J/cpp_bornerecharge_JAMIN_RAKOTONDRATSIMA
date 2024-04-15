#ifndef BOUTON_H
#define BOUTON_H

#include <memoire_borne.h>
#include <donnees_borne.h>

class Bouton
{
	
    public :
    entrees* io;
    Bouton();
    int charge();
    int stop();
};

#endif

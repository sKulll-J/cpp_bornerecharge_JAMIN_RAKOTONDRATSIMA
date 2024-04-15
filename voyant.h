#ifndef VOYANT_H
#define VOYANT_H

#include <memoire_borne.h>
#include <donnees_borne.h>

class Voyant
{
    public :
    entrees* io;
    Voyant();
    void set_dispo(int etat);
    void set_default(int etat);
    void set_charge(int etat);

    void blink_charge();

    int dispo();


};
#endif

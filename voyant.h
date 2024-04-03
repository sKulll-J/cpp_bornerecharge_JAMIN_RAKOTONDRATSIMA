#ifndef VOYANT_H
#define VOYANT_H

class Voyant
{
    public :
    Voyant();
    void set_dispo(int etat);
    void set_default(int etat);
    void set_charge(int etat);

    void blink_charge();

    int dispo();


};
#endif
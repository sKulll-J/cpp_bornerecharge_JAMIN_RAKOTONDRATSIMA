#ifndef VOYANTS_H
#define VOYANTS_H

class voyant
{
    public :
    voyant();
    void set_dispo(int etat);
    void set_default(int etat);
    void set_charge(int etat);

    void blink_charge();

    int dispo();


}
#endif
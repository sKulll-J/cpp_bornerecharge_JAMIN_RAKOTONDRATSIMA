#ifndef GENERATEUR_H
#define GENERATEUR_H

class Generateur 
{
    public :
    Generateur ();
    void generer_PWM(int etat);
    void ouvrir_AC();
    void fermer_AC();
    void deconnecter();
    void charger();
};

#endif
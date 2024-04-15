#ifndef GENERATEUR_H
#define GENERATEUR_H

class Generateur 
{
	private :
	int carte_id;
    public :
    Generateur ();
    void generer_PWM(int etat);
    void ouvrir_AC();
    void fermer_AC();
    void deconnecter();
    //void charger(Voyant voyant, Prise prise, Generateur generateur);
};

#endif

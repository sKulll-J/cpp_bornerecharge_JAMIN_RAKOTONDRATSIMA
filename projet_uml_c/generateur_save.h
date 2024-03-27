#ifndef GENERATEUR_SAVE_H
#define GENERATEUR_SAVE_H

void generateur_init();

//float generateur_tension();

void generateur_generer_PWM(int etat);

void generateur_ouvrir_AC();
void generateur_fermer_AC();

//void generateur_deconnecter();

void generateur_charger();


#endif

#ifndef VOYANTS_H
#define VOYANTS_H

void init_voyant();

void voyants_set_charge();

void voyants_set_dispo(int etat);
void voyants_set_default(int etat);
void voyants_set_charge(int etat);

void voyants_blink_charge();

int voyants_dispo();



#endif

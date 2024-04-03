
#include "lecteurcarte.h"
#include<iostream>

using namespace std;

LecteurCarte::LecteurCarte()
{
	
}

int LecteurCarte::lire_carte()
{
	initialisations_ports();
	cout<<"Lecture"<<endl;
	
	cout<<"Inserez votre carte"<<endl;
	attente_insertion_carte();
	cout<<">Carte insérée .."<<endl<<endl;
	cout<<">Carte numéro "<<lecture_numero_carte()<<endl;
	attente_retrait_carte();
	liberation_ports();
	return lecture_numero_carte();
}


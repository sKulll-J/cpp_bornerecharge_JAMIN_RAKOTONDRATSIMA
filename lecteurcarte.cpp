#include "lecteurcarte.h"
#include<iostream>

using namespace std;

LecteurCarte :: LecteurCarte()
{
	initialisations_ports();

}
void LecteurCarte :: lire_carte()
{	
	cout<<"==== \nnew Lecture\n"<<endl;
	
	cout<<"Inserez votre carte"<<endl;
	attente_insertion_carte();
	
	cout<<">Carte insérée .." << endl << endl;
	cout<<">Carte numéro " << lecture_numero_carte() << endl;
		
	attente_retrait_carte();

}
int LecteurCarte :: get_id()
{
	return lecture_numero_carte();
}

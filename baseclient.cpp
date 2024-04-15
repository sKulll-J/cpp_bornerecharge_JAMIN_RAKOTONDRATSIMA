#include<stdio.h>

#include <unistd.h>
#include "baseclient.h"
#include<fstream>
 
#include<lcarte.h>

using namespace std;

int Baseclient :: authentifier( int numero_carte )
{	
	int carteNum;
	string ownerName;
	string mdp;
	
	string mdpToCheck="";
	string ownerCarte;
	
	ifstream datas("baseclient.txt");
	

	
	while (datas>>carteNum>>ownerName>>mdp)
	{
		if(carteNum==numero_carte)
		{
			mdpToCheck=mdp;
			ownerCarte = ownerName;
		}
	}
	
	if(mdpToCheck!="")
	{
		string _mdp;
		cout<<"Bonjour "<<ownerCarte<<" !\nVeuillez rentrer votre mot de passe :";
		cin>>_mdp;
		if(_mdp==mdp){
			cout<<"Mot de passe validé\n";
			return 1; //si mdp valide
		}
		else
		{
			cout<<"Mot de passe non valide\nRetirez la carte puis rééseyez.\n";
		}
	}
	else
		cout<<"Numéro de carte inconnue.\nRetirez la carte puis rééseyez.\n";
	
	// attend une saisie de l'utilisateur de son mdp
	// compare avec la base de donnée id_carte mdp
	return 0 ; // si mdp ok

	// echec sinon
}

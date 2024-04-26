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
		cout<<"...\n>Bonjour "<<ownerCarte<<" !\n!! Veuillez rentrer votre mot de passe :";
		cin>>_mdp;
		
		//cout<<_mdp<<" - "<<mdpToCheck<<endl;
		if(_mdp==mdpToCheck){
			cout<<">Mot de passe validé\n";
			return 1; //si mdp valide
		}
		else
		{
			cout<<"> mot de passe non valide\n!! Retirez la carte puis réésayez.\n";
		}
	}
	else
		cout<<">Numéro de carte inconnue.\n!! Retirez la carte puis rééseyez.\n";
	
	// attend une saisie de l'utilisateur de son mdp
	// compare avec la base de donnée id_carte mdp
	return 0 ; // si mdp ok

	// echec sinon
}

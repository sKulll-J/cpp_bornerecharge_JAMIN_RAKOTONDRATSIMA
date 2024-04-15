#include <iostream>
#include "generateur.h"

#include<donnees_borne.h>
#include<memoire_borne.h>

using namespace std;

//entrees* io ;
//int shmid ;

Generateur :: Generateur()
{
	io=acces_memoire(&shmid);
}

/*
void Generateur :: charger(Voyant voyant, Prise prise, Generateur generateur)
{
	voyant.set_charge(2); // Voyant charge => ROUGE
	prise.deverouiller_trappe(); 
	
	
// MEF
	typedef enum _etat {A,B,C,D,E,F, pre_deconnect, deconnectn END} etat;
	etat etat_present, etat_suivant ;
	
	// initialisation 
	etat_present = A ;
	etat_suivant = A ;
	
	cout << "Branchez la prise\n" << endl;
	while(etat_present!=END)
	{
		//Block F : transitions
		if ((etat_present == A) && (io->gene_u == 9) && io->gene_pwm==DC)
		{	etat_suivant = B ;
			cout << ">prise branchee \n" << endl ;
		}
		
 		else if (etat_present == B)
		{	
			if ((io->gene_u == 9) && io->gene_pwm == AC_1K )
			{	etat_suivant = C;
				cout << "connection à la voiture\n" << endl;
			}
			else if (io->bouton_stop ==1)
			{	etat_suivant = E;
				cout << "demande STOP\n" << endl;
			}
		}
		else if (etat_present == C)
		{
			if(io->gene_u == 6)
			{	etat_suivant = D;
				cout << "charge en cours ...\n" <<endl;
			}
			else if(io->bouton_stop==1)
			{	etat_suivant=E;
				cout << "demande STOP\n" << endl;
			}
		}
		else if (etat_present == D)
		{
			if( (io->bouton_stop==1)||(io->gene_u == 9) && (io->gene_pwm !=DC) )
			{
				etat_suivant=E;
				cout << "Fin de charge\n" << endl;
			}
		}
		else if (etat_present == E)
		{
			if (io->gene_pwm = DC)
			{	etat_suivant =F;
				cout << "recuperer vehicule\n" <<endl ;
			}
		}
		//-----------------------------------------------------
		else if (etat_present == F)
		{	
			attente_insertion_carte();
			carte_id = lecture_numero_carte();
			
			if (lecteurcarte.get_id() == carte_id)
			{
				cout << "\n---\nID Correct\n---\n" <<endl;
				if (baseclient.authentifier(carte_id)==1)
				{
					// authentification réussie
					cout << "debrancher vehicule \n" << endl;
					voyant.set_charge(0); // voyant charge : off
					prise.deverouiller_trappe();
					etat_suivant = deconnect;
				}
				else
				{	//authentification echec
					cout << "mauvais mdp \n" <<endl ;
					cout << "retirer carte \n"<< endl;
					attente_retrait_carte();
					cout << "carte retiree\n" <<endl;
					etat_suivant=F;
				}
			}
			else
			{
				cout <<"CECI N'EST PAS VOTRE VEHICULE \n" <<endl;
				cout <<"retirer carte et reessayer\n"<<endl;
				attente_retrait_carte();
				cout << "carte retiree\n" <<endl;
				etat_suivant=F;
			}
		}
		else if (etat_present == deconnect)
		{
			if ( (io->gene_u=12) && (io->gene_pwm = DC)
			{
				prise.verouiller_trappe();
				cout << "retirer carte \n"<< endl;
				attente_retrait_carte();
				cout << "carte retiree\n" <<endl;
				etat_suivant=END;
			}
		}
		//-----------------------------------------------------
		//Blok M : mémoire
		etat_present = etat_suivant;

		//Block G : sorties
		if(etat_present == A)
		{
			voyant.set_charge(2); // Voyant charge => Rouge
			prise.deverouiller_trappe();
			generateur.generer_PWM(1); // 12V DC output
	
		}

		if(etat_present == B)
		{
			prise.set_prise(1); // Voyant Prise => Vert
			prise.verouiller_trappe();
			generateur.generer_PWM(2); // AC_1K output
		}
		
		if(etat_present == C)
		{
			generateur.fermer_AC();
			generateur.generer_PWM(3); // AC_CL output
		}
		
		if(etat_present == D)
		{
			generateur.generer_PWM(3); // AC_CL output
		}
		if(etat_present == E)
		{
			generateur.ouvrir_AC();
			voyant.set_charge(1); // Voyant charge => Vert
			generateur.generer_PWM(1); // DC output
		}
	}
}
*/
void Generateur :: ouvrir_AC()
{
	io->contacteur_AC = 0;
}

void Generateur :: fermer_AC()
{
	io->contacteur_AC = 1;
}



void Generateur :: generer_PWM(int etat)
{
	switch(etat)
	{
		case 0:
			io->gene_pwm = STOP;
			break;
		case 1 :
			io->gene_pwm = DC;
			break;
		case 2 :
			io->gene_pwm = AC_1K;
			break;
		case 3 :
			io->gene_pwm =  AC_CL;
			break;
		default :
			io->gene_pwm = STOP;
			break;	
	}		
}
